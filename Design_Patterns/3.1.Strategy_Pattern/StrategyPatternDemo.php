#!/usr/bin/php
<?php

namespace Strategy_Pattern;

include "Context.php";

$context = new Context(new OperationAdd());

echo ("10 + 5 = " . $context->executeStrategy(10, 5) . "\n");

$context = new Context(new OperationSubstract());
echo ("10 - 5 = " . $context->executeStrategy(10, 5) . "\n");

$context = new Context(new OperationMultiply());
echo ("10 * 5 = " . $context->executeStrategy(10, 5) . "\n");

// echo get_class($context) . "\n";
