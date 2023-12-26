import config
import songs


songs_data = songs.get_songs()

song_index = 0
note_index = 0


def get_handler(command: str):
    return {
        'PRINT': print_handler,
        'PREV_SONG': prev_song_handler,
        'NEXT_SONG': next_song_handler,
        'NEXT_NOTE': next_note_handler,
        'GET_TITLE': get_title_handler,
        'GET_NOTE': get_note_handler,
    }.get(command, default_handler)


def default_handler(*values: list[str]):
    print(f"Default handler with values {values} was called")


def print_handler(*values: list[str]):
    print(f'ARDUINO MESSAGE: {config.COMMAND_SEPARATOR.join(values)}')


def prev_song_handler(*values: list[str]):
    prev_song()
    return 'NEW_SONG'


def next_song_handler(*values):
    next_song()
    return 'NEW_SONG'


def next_note_handler(*values):
    changed = next_note()
    if changed == 'note':
        return 'NEW_NOTE'
    if changed == 'song':
        return 'NEW_SONG'


def get_title_handler(*values):
    song = songs_data[song_index]
    return f"TITLE {song_index + 1}.{song['title']}"


def get_note_handler(*values):
    song = songs_data[song_index]
    return f"NOTE {song['melody'][note_index]} {song['durations'][note_index]}"


def prev_song():
    global song_index, note_index
    song_index -= 1
    note_index = 0
    if song_index == -1:
        song_index = len(songs_data) - 1


def next_song():
    global song_index, note_index
    song_index += 1
    note_index = 0
    if song_index == len(songs_data):
        song_index = 0


def next_note():
    global song_index, note_index
    note_index += 1
    if note_index == len(songs_data[song_index]['melody']):
        next_song()
        return 'song'
    return 'note'
