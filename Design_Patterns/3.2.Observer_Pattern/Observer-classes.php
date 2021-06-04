<?php

namespace Observer_Pattern;

include "Subject.php";

class BinaryObserver extends Observer
{
    public function __construct(Subject $subject)
    {
        $this->subject = $subject;
        $this->subject->attach($this);
    }

    public function update()
    {
        echo ("Binary String: " . decbin($this->subject->getState()) . "\n");
    }
}

class OctalObserver extends Observer
{
    public function __construct(Subject $subject)
    {
        $this->subject = $subject;
        $this->subject->attach($this);
    }

    public function update()
    {
        echo ("Octal String: " . decoct($this->subject->getState()) . "\n");
    }
}

class HexaObserver extends Observer
{
    public function __construct(Subject $subject)
    {
        $this->subject = $subject;
        $this->subject->attach($this);
    }
    public function update()
    {
        echo ("Hex String: " . dechex($this->subject->getState()) . "\n");
    }
}
