import whisper
import torch
import torchaudio
from pyannote.audio import Pipeline
from pydub import AudioSegment
import re
import os
import shutil

def hello_stt():
    print("Hello, World! version 1.6")

def split_files(filename: str) -> str:
    # 결과를 저장할 디렉토리
    split_dir = "/content/splittedfiles"
    filepath = "/content/drive/MyDrive/MeetingAudio/" + filename # 파일 이름 설정

    os.makedirs(split_dir, exist_ok=True)

    # 오디오 파일 로드
    audio = AudioSegment.from_wav(filepath)

    # 시간 정보 파일 읽기
    with open("pyannote.txt", 'r', encoding='utf-8') as f:
        lines = f.readlines()

    segment_index = 0  # 구간 번호

    for line in lines:
        parts = line.strip().split('\t')
        if len(parts) < 3:
            continue  # 잘못된 형식은 건너뜀

        start_time = float(parts[0])  # 시작 시간 (초)
        end_time = float(parts[1])    # 종료 시간 (초)
        speaker_label = parts[2].strip()  # 화자 ID

        # 초 단위 시간을 밀리초로 변환
        start_ms = int(start_time * 1000)
        end_ms = int(end_time * 1000)

        # 오디오 구간 분리
        segment_audio = audio[start_ms:end_ms]

        # 오디오 길이가 1초 미만인 경우 건너뜀
        if len(segment_audio) < 1000:  # 길이가 1000ms (1초) 미만인 경우
            continue

        # 시간 형식 변경 (HH:MM:SS)
        start_time_str = f"{int(start_time // 3600):02d}:{int((start_time % 3600) // 60):02d}:{int(start_time % 60):02d}"
        end_time_str = f"{int(end_time // 3600):02d}:{int((end_time % 3600) // 60):02d}:{int(end_time % 60):02d}"

        # 구간 번호 증가
        segment_index += 1

        # 번호를 4자리로 맞추기
        segment_index_str = str(segment_index).zfill(4)  # 또는 f"{segment_index:04}"

        # 출력 파일 경로
        output_path = os.path.join(split_dir, f"{segment_index_str}_{speaker_label}_{start_time_str}_{end_time_str}.wav")
        segment_audio.export(output_path, format="wav")

    return split_dir

def delete_files(split_dir: str):    
    # 디렉토리가 존재하는지 확인
    if os.path.exists(split_dir):
        # 하위 파일 삭제
        for filename in os.listdir(split_dir):
            file_path = os.path.join(split_dir, filename)
            try:
                if os.path.isfile(file_path) or os.path.islink(file_path):
                    os.unlink(file_path)  # 파일 또는 심볼릭 링크 삭제
                elif os.path.isdir(file_path):
                    shutil.rmtree(file_path)  # 디렉토리 삭제
            except Exception as e:
                print(f"Error deleting {file_path}: {e}")
        print(f"모든 파일이 {split_dir}에서 삭제되었습니다.")
    else:
        print(f"디렉토리 {split_dir}가 존재하지 않습니다.")

def diarization(filename: str):
    filepath = "/content/drive/MyDrive/MeetingAudio/" + filename # 파일 이름 설정
  
    authtoken_pyannote = "YOUR_TOKEN"

    pipeline = Pipeline.from_pretrained(
        "pyannote/speaker-diarization-3.1", use_auth_token=authtoken_pyannote
    )

    pipeline.to(torch.device("cuda")) #GPU 사용
    diarization_result = pipeline(filepath) # pyannote의 화자분리

    # 화자분리의 결과를 첨부된 파일 형식으로 저장하는 코드
    f_time = open("pyannote.txt", "w", encoding='utf-8')

    # diarization_result에서 정보를 추출하여 형식에 맞게 작성
    for turn, _, speaker in diarization_result.itertracks(yield_label=True):
        start = f"{turn.start:.3f}"  # float를 문자열로 포맷
        end = f"{turn.end:.3f}"  # float를 문자열로 포맷
        print(f'{start}\t{end}\t {speaker}', file=f_time)  # 추가 포맷팅 없이 출력
    
    f_time.close()

def transcribe(filename: str) -> str:
    split_dir = split_files(filename)
    # STT 결과를 저장할 파일
    output_filepath = "/content/drive/MyDrive/MeetingAudio/STT.txt"

    # Whisper 모델 로드
    model = whisper.load_model("large-v3-turbo")  # 또는 "small", "medium", "large" 등

    # 결과 파일 쓰기
    with open(output_filepath, 'w', encoding='utf-8') as output_file:
        # 입력 디렉토리 내 파일 리스트 가져오기
        audio_files = sorted([f for f in os.listdir(split_dir) if f.endswith('.wav')])

        for audio_file in audio_files:
            audio_path = os.path.join(split_dir, audio_file)

            try:
                # Whisper 모델로 STT 수행
                result = model.transcribe(audio_path, language="ko", task="transcribe")  # 한국어라면 `language="ko"` 추가
                stt_text = result["text"]

                # 파일 이름에서 발화자와 시간을 추출
                # 예: "0001_SPEAKER_02_00:00:00_00:00:14.wav"
                file_parts = audio_file.rstrip('.wav').split('_')
                speaker = f"{file_parts[1]}_{file_parts[2]}"  # SPEAKER_02
                start_time = file_parts[3].replace(':', '.')  # 00:00:00 -> 00.00.00
                end_time = file_parts[4].replace(':', '.')  # 00:00:14 -> 00.00.14

                # 출력 형식 지정
                output_file.write(f"[{start_time}\t{end_time}]\n")
                output_file.write(f"{speaker}\t\"{stt_text}\"\n\n")

                # 결과 저장
                #output_file.write(f"{stt_text_cleaned}\n")

            except Exception as e:
                print(f"Error processing {audio_file}: {e}")
    delete_files(split_dir)
    return output_filepath