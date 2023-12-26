import json
import config


def get_songs():
    with open(config.SONGS_FILE, 'r') as file:
        return json.load(file)

