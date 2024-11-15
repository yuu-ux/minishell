import shlex
import subprocess

OK_COLOR = '\033[92m'    # 緑
NG_COLOR = '\033[91m'    # 赤
RESET_COLOR = "\033[0m"  # リセット

# テスト対象のパイプライン
pipelines = [
    'cat < input > output',
    'cat < input >> output',
    'cat << EOF >> output',
    'command < in1 < in2 > out1 > out2',
    'cat < file | grep "test" > output',
    'cat file | grep "test" | wc -l > output',
    'cat < input | sort | uniq > output',
    'cat << EOF | grep "test" >> output',
    'echo "Hello   World"',
    "echo 'Hello   World'",
    'echo "text with | < > >>"',
    'echo ""',
    "echo ''",
    'cat    <    file   |   wc',
    'echo "Hello    World"',
    'cat<file|wc',
    'cat <> file',
    'cat << "EOF" | grep "test" >> "out put"',
    'echo $"variable"',
    'cat < file1>file2',
]
# Python側でトークン化
def python_tokenizer(pipeline):
    tokens = list(shlex.shlex(pipeline, punctuation_chars=True))
    return tokens

# Cプログラムの実行
def c_program_tokenizer(pipeline):
    process = subprocess.run(
        ['./tokenize_test', pipeline],
        capture_output=True,
        text=True,
        check=False
    )
    if process.returncode != 0:
        print('Cプログラム実行エラー:', process.stderr)
        return None
    return process.stdout.strip().split('\n')

# テストの実行
def tester(pipeline):
    python_tokens = python_tokenizer(pipeline)
    c_tokens = c_program_tokenizer(pipeline)

    if c_tokens is None:
        print('Cプログラムの出力がありません')
        return

    # 比較
    if python_tokens == c_tokens:
        print(f'{OK_COLOR}[OK]{RESET_COLOR}')
    else:
        print(f'{NG_COLOR}[NG]{RESET_COLOR}')
        print('Python側トークン:', python_tokens)
        print('Cプログラム側トークン:', c_tokens)

# テスト実行
for pipeline in pipelines:
    tester(pipeline)
