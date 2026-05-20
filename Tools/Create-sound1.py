import wave
import os

# ==============================
# Audio Configuration
# ==============================
SAMPLE_RATE = 8000     # Samples per second (Hz)
DURATION = 180           # Duration in seconds
NUM_SAMPLES = SAMPLE_RATE * DURATION

OUTPUT_FILE = "sound8.wav"

# ==============================
# Bytebeat Formula Function
# ==============================
def bytebeat(t):
    """
    Generates a single audio sample based on time 't'.
    This is the core formula (same as your C++ version).
    """
    return (t >> 6 ^ t & t >> 9 ^ t >> 12 | ((t >> 6 | t << 1) + (t >> 5 | t << 3 | t >> 3) | t >> 2 | t << 1));

# ==============================
# Generate Audio Buffer
# ==============================
def generate_audio():
    buffer = bytearray()

    for t in range(NUM_SAMPLES):
        value = bytebeat(t)

        # Ensure value is within 8-bit range (0–255)
        buffer.append(value & 0xFF)

    return buffer

# ==============================
# Save to WAV File
# ==============================
def save_wav(buffer):
    with wave.open(OUTPUT_FILE, "wb") as wav_file:
        wav_file.setnchannels(1)        # Mono
        wav_file.setsampwidth(1)        # 8-bit audio
        wav_file.setframerate(SAMPLE_RATE)
        wav_file.writeframes(buffer)

# ==============================
# Play Audio (Windows)
# ==============================
def play_audio():
    os.system(f"start {OUTPUT_FILE}")

# ==============================
# Main Program
# ==============================
def main():
    print("Generating audio...")
    buffer = generate_audio()

    print("Saving WAV file...")
    save_wav(buffer)

    print("Playing audio...")
    play_audio()

    print("Done.")

if __name__ == "__main__":
    main()
