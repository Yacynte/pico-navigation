from pynput import keyboard

def on_press(key):
    try:
        print(f'Key {key.char} pressed')
    except AttributeError:
        print(f'Special key {key} pressed')

listener = keyboard.Listener(on_press=on_press)
listener.start()

# Keep the program running
listener.join()
