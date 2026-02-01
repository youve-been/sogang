import os
from openai import OpenAI

def hello_gpt():
    print("Hello, World! version 1.6")

os.environ["OPENAI_API_KEY"] = "YOUR_API_KEY"

client = OpenAI()

# system_prompt = "먼저 전체 텍스트 내용을 요약해주고, 그 다음에 요약의 근거를 시간과 함께 SPEAKER 별로 한두 문장씩 추출해줘"
system_prompt = "회의 안건 한 줄 요약해줘 명사형 종결문으로 써줘"
system_prompt2 = "회의 주요 안건 한 줄 요약해줘 명사형 종결문으로 써줘"
system_prompt3 = "회의 내용을 자세하게 요약해줘 이건 동사형 종결문으로 존댓말로 써줘"
system_prompt4 = "회의 결과를 한 줄로 요약해줘"

summary=[
    {
        "id":0,
        "name":"안건",
        "item":""
    },
    {
        "id":1,
        "name":"일시",
        "item":""
    },
    {
        "id":2,
        "name":"책임자명",
        "item":""
    },
    {
        "id":3,
        "name":"장소",
        "item":""
    },
    {
        "id":4,
        "name":"참석인원",
        "item":""
    },
    {
        "id":5,
        "name":"주요 안건",
        "item":""
    },
    {
        "id":6,
        "name":"회의 내용",
        "item":""
    },
    {
        "id":7,
        "name":"회의 결과",
        "item":""
    },
]

def use_gpt(temperature, system_prompt, audio_file):
    response = client.chat.completions.create(
        model="gpt-4o",
        temperature=temperature,
        messages=[
            {
                "role": "system",
                "content": system_prompt
            },
            {
                "role": "user",
                "content": audio_file
            }
        ]
    )

    return response.choices[0].message.content

def summarize(filename: str) -> list:
    f = open(filename, 'r', encoding='utf-8')
    text_split = f.readlines()
    f.close()

    joined_text = "".join(text_split)
    new_text=""
    new_text+=use_gpt(0, system_prompt, joined_text)
    summary[0]["item"] = new_text

    new_text=""
    new_text+=use_gpt(0, system_prompt2, joined_text)
    summary[5]["item"] = new_text

    new_text=""
    new_text+=use_gpt(0, system_prompt3, joined_text)
    summary[6]["item"] = new_text

    new_text=""
    new_text+=use_gpt(0, system_prompt4, joined_text)
    summary[7]["item"] = new_text

    return summary