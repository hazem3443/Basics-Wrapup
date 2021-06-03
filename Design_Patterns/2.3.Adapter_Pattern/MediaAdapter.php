<?php

namespace Adapter_Pattern;

include "MediaPlayer.php";

interface MediaPlayer
{
    public function play(String $audioType, String $fileName);
}

class MediaAdapter implements MediaPlayer
{
    protected AdvancedMediaPlayer $advancedMusicPlayer;

    public function __construct(String $audioType)
    {
        if (strcasecmp($audioType, "vlc") == 0) {
            $this->advancedMusicPlayer = new VlcPlayer();
        } else if (strcasecmp($audioType, "mp4") == 0) {
            $this->advancedMusicPlayer = new Mp4Player();
        }
    }

    public function play(String $audioType, String $fileName)
    {
        if (strcasecmp($audioType, "vlc") == 0) {
            $this->advancedMusicPlayer->playVlc($fileName);
        } else if (strcasecmp($audioType, "mp4") == 0) {
            $this->advancedMusicPlayer->playMp4($fileName);
        }
    }
}

class AudioPlayer implements MediaPlayer
{
    protected MediaAdapter $mediaAdapter;

    public function play(String $audioType, String $fileName)
    {
        //built-in support to play mp3 music files the default functionality
        if (strcasecmp($audioType, "mp3") == 0) {
            echo ("Playing mp3 file. Name: " . $fileName);
        } else if (strcasecmp($audioType, "vlc") == 0 || strcasecmp($audioType, "mp4") == 0) {        //mediaAdapter is providing support to play other file formats
            $this->mediaAdapter = new MediaAdapter($audioType);
            $this->mediaAdapter->play($audioType, $fileName);
        } else {
            echo ("Invalid media. " . $audioType . " format not supported\n");
        }
    }
}
