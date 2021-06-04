<?php

namespace Observer_Pattern;

abstract class Observer
{
    protected  $subject;
    public abstract function update();
}
