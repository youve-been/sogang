import docx
from docx import Document


def hello_word():
    print("Hello, World! version 1.6")

# 특정 위치에 필요한 것을 넣는 코드
def add_custom_text_to_adjacent_empty_cells(docx_path, output_path, content_dict):
    doc = Document(docx_path)
    print(content_dict)
    for table in doc.tables:
        for row_idx, row in enumerate(table.rows):
            for col_idx, cell in enumerate(row.cells):
                cell_text = cell.text.strip()

                if cell_text in content_dict:
                    text_to_add = content_dict[cell_text]

                    if col_idx + 1 < len(row.cells) and not row.cells[col_idx + 1].text.strip():
                        row.cells[col_idx + 1].text = text_to_add  # Add text to the right empty cell

                    elif row_idx + 1 < len(table.rows) and not table.rows[row_idx + 1].cells[col_idx].text.strip():
                        table.rows[row_idx + 1].cells[col_idx].text = text_to_add  # Add text to the below empty cell

    doc.save(output_path)
    