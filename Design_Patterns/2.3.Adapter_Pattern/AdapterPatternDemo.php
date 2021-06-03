#!/usr/bin/php
<?php

namespace Adapter_Pattern;

include "MediaAdapter.php";

$audioPlayer = new AudioPlayer();

$audioPlayer->play("mp3", "beyond the horizon.mp3\n");
$audioPlayer->play("mp4", "alone.mp4\n");
$audioPlayer->play("vlc", "far far away.vlc\n");
$audioPlayer->play("avi", "mind me.avi\n");
