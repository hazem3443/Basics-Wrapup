<?php

namespace Strategy_Pattern;

include "Strategy.php";

class Context
{
    private Strategy $strategy;

    public function __construct(Strategy $strategy)
    {
        $this->strategy = $strategy;
    }

    public function executeStrategy(int $num1, int $num2)
    {
        return $this->strategy->doOperation($num1, $num2);
    }
}
