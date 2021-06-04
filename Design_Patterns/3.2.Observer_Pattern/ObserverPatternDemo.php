#!/usr/bin/php
<?php

namespace Observer_Pattern;

include "Observer_class_type.php";
include "Observer-classes.php";

$subject = new Subject();

new HexaObserver($subject);
new OctalObserver($subject);
new BinaryObserver($subject);

echo ("First state change: 15\n");
$subject->setState(15);
echo ("Second state change: 10\n");
$subject->setState(10);
