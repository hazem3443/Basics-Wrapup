<?php

class queuetype
{
    public $q;
    public $front;
    public $rear;
    public $itemCount;

    function __construct($q, $front, $rear, $itemCount)
    {
        $this->q = $q;
        $this->front = $front;
        $this->rear = $rear;
        $this->itemCount = $itemCount;
    }
}

$Queobj = new queuetype(range(1, 10), 0, -1, 0);

function enque(&$Queobj, $data)
{
    $Queobj->itemCount++;
    $Queobj->q[++$Queobj->rear] = $data; //till the count($Queobj.q)
}

function deque(&$Queobj)
{
    $Queobj->itemCount--;
    return $Queobj->q[$Queobj->front++]; //0
}

function itemCount(&$Queobj)
{
    return $Queobj->itemCount;
}


enque($Queobj, 10);
enque($Queobj, 11);
enque($Queobj, 12);
enque($Queobj, 13);

echo deque($Queobj) . "\n";
echo deque($Queobj) . "\n";
echo deque($Queobj) . "\n";
echo deque($Queobj) . "\n";

enque($Queobj, 9);
enque($Queobj, 9);
enque($Queobj, 9);
enque($Queobj, 9);

print_r($Queobj);
