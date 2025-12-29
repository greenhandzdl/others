# python
#!/usr/bin/env python3
'''
paste.py - 逐字符模拟键盘输入脚本
'''
import sys
import time

try:
    import pyautogui
except Exception:
    print("缺少依赖：请先运行 `pip install pyautogui` 并授予辅助功能权限。")
    sys.exit(1)

# pyautogui global settings: pyautogui.PAUSE is applied after every PyAutoGUI call (default 0.1s)
# If you want truly minimal pauses, set PYAUTOGUI_GLOBAL_PAUSE = 0.0
PYAUTOGUI_GLOBAL_PAUSE = 0.0
PYAUTOGUI_FAILSAFE = False
# Apply the settings to the imported module
pyautogui.PAUSE = PYAUTOGUI_GLOBAL_PAUSE
pyautogui.FAILSAFE = PYAUTOGUI_FAILSAFE

# Configuration constants (can be adjusted by user)
START_DELAY = 3.0        # seconds to wait before starting simulated typing
CHAR_INTERVAL = 0.1     # seconds between each character when typing
# If True, ignore CHAR_INTERVAL and send characters with no delay (fastest possible)
NO_INTERVAL = True
# If True, attempt to input Chinese characters by typing their pinyin then pressing space
# Requires a Chinese Pinyin input method (e.g. "Pinyin - Simplified") active in the target
USE_PINYIN_INPUT = False

# Optional dependency: pypinyin to convert Chinese characters to pinyin
try:
    import importlib
    _pypinyin_mod = importlib.import_module('pypinyin')
    _pypinyin_pinyin = getattr(_pypinyin_mod, 'pinyin', None)
    _pypinyin_Style = getattr(_pypinyin_mod, 'Style', None)
except Exception:
    _pypinyin_pinyin = None
    _pypinyin_Style = None


def is_chinese_char(ch: str) -> bool:
    """Return True if ch is a CJK Unified Ideograph (basic range)."""
    if not ch:
        return False
    code = ord(ch)
    # Basic CJK Unified Ideographs range: 0x4E00 - 0x9FFF
    return 0x4E00 <= code <= 0x9FFF


def chinese_chunk_to_pinyin(chunk: str) -> str:
    """Convert a chunk of Chinese characters to a concatenated pinyin string.

    Uses pypinyin if available; otherwise returns an empty string to signal fallback.
    Example: '中文' -> 'zhongwen'
    """
    if not chunk:
        return ''
    # attempt to import pypinyin dynamically to avoid static-analysis calling None
    try:
        import importlib
        mod = importlib.import_module('pypinyin')
        py_func = getattr(mod, 'pinyin', None)
        PyStyle = getattr(mod, 'Style', None)
        if py_func is None or PyStyle is None or not callable(py_func):
            return ''
        # get pinyin for each character, no tone marks
        try:
            py_list = py_func(chunk, style=PyStyle.NORMAL, strict=False)
        except Exception:
            return ''
    except Exception:
        return ''
    # pinyin() should return list of lists; guard in case it's malformed
    if not isinstance(py_list, (list, tuple)):
        return ''
    try:
        syllables = [item[0] if item else '' for item in py_list]
    except Exception:
        return ''
    return ''.join(syllables)


def simulate_typing(text: str, interval: float = CHAR_INTERVAL):
    """
    逐字符模拟键盘输入：
    - '\n' -> press 'enter'
    - '\t' -> press 'tab'
    - 连续中文字符：如果 USE_PINYIN_INPUT 为 True 且安装了 pypinyin，
      将连续中文字符转换为拼音后一次性键入，然后按空格以通过输入法确认。（需要目标为拼音输入法）
    其他字符逐字符写入，间隔为 interval 秒

    如果全局 NO_INTERVAL 为 True，则会忽略传入的 interval 并使用 0.0（无间隔）。
    """
    effective_interval = 0.0 if NO_INTERVAL else (interval if interval is not None else CHAR_INTERVAL)

    i = 0
    n = len(text)
    while i < n:
        ch = text[i]
        if ch == '\r':
            i += 1
            continue
        # handle newlines and tabs
        if ch == '\n':
            pyautogui.press('enter')
            i += 1
            continue
        if ch == '\t':
            pyautogui.press('tab')
            i += 1
            continue

        # If enabled and current char is Chinese, gather a chunk of consecutive Chinese chars
        if USE_PINYIN_INPUT and is_chinese_char(ch):
            j = i
            while j < n and is_chinese_char(text[j]):
                j += 1
            chunk = text[i:j]
            pinyin_text = chinese_chunk_to_pinyin(chunk)
            if pinyin_text:
                # Type the pinyin (no separators) then press space to commit via IME
                # For IME stability, use a small non-zero interval when typing pinyin even
                # if NO_INTERVAL is set. Zero-interval often makes the IME miss the input.
                pinyin_interval = effective_interval if effective_interval > 0.0 else 0.005
                pyautogui.write(pinyin_text, interval=pinyin_interval)
                # give IME a short moment to show candidates, then commit with space
                time.sleep(0.02)
                pyautogui.press('space')
                # short pause after committing before continuing
                time.sleep(0.01)
            else:
                # fallback: type the original characters directly (may not work for Chinese)
                for c in chunk:
                    pyautogui.write(c, interval=effective_interval)
            i = j
            continue

        # default: type the character
        # For speed, gather a run of consecutive non-Chinese, non-special chars
        j = i
        while j < n and text[j] not in ('\r', '\n', '\t') and (not is_chinese_char(text[j])):
            j += 1
        segment = text[i:j]
        if segment:
            pyautogui.write(segment, interval=effective_interval)
        i = j

def main():
    print("请粘贴或输入要模拟的文本（支持多行），完成后按 Ctrl+D 结束：")
    try:
        text = sys.stdin.read()
    except KeyboardInterrupt:
        print("\n已取消。")
        return

    if not text:
        print("未读取到任何文本，退出。")
        return

    mode_note = "（无间隔模式）" if NO_INTERVAL else ""
    if USE_PINYIN_INPUT:
        mode_note += "（拼音输入模式）"
    print("将在 {} 秒后开始模拟键盘输入，请切换到目标窗口...{}".format(START_DELAY, mode_note))
    time.sleep(START_DELAY)

    try:
        simulate_typing(text, interval=CHAR_INTERVAL)
    except Exception as e:
        print("模拟输入时发生错误：", e)
    else:
        print("已完成模拟输入。")

if __name__ == "__main__":
    main()
