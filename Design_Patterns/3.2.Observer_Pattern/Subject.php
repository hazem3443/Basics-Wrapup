<?php

namespace Observer_Pattern;

class Subject
{

    private $observers = [];
    private int $state; //data may be string or object or array

    public function getState()
    {
        return $this->state;
    }

    public function setState(int $state)
    {
        $this->state = $state;
        $this->notifyAllObservers();
    }

    public function attach(Observer $observer)
    {
        array_push($this->observers, $observer);
    }

    public function notifyAllObservers()
    {
        for ($i = 0; $i < count($this->observers); $i++) {
            $this->observers[$i]->update();
        }
    }
}
