<?php

namespace Adapter_Pattern;


interface AdvancedMediaPlayer
{
    public function playVlc(String $fileName);
    public function playMp4(String $fileName);
}


class VlcPlayer implements AdvancedMediaPlayer
{

    public function playVlc(String $fileName)
    {
        echo ("Playing vlc file. Name: " . $fileName);
    }

    public function playMp4(String $fileName)
    {
        //do nothing
    }
}

class Mp4Player implements AdvancedMediaPlayer
{

    public function playVlc(String $fileName)
    {
        //do nothing
    }

    public function playMp4(String $fileName)
    {
        echo ("Playing mp4 file. Name: " . $fileName);
    }
}
