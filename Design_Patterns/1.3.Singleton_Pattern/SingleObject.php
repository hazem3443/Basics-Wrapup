<?php

namespace SingletonPattern;

//Any method declared as static is accessible without the creation of an object. 
// Static functions are associated with the class, not an instance of the class.
// They are permitted to access only static methods and static variables.
class SingleObject
{
    //create an object of SingleObject
    private static $instance = null;
    //create private static variables here such that
    /*
    private $namee = "default";
    */
    // private $conn;

    // private $host = 'localhost';
    // private $user = 'db user-name';
    // private $pass = 'db password';
    // private $name = 'db name';

    //make the constructor private so that this class cannot be accessed from outside
    //instantiated
    private function __construct()
    {
        echo "constructed\n";
        //do something like db connection logic that created once for certain class

        // $this->conn = new PDO(
        //     "mysql:host={$this->host};
        //     dbname={$this->name}",
        //     $this->user,
        //     $this->pass,
        //     array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES 'utf8'")
        // );
    }

    //Get the only object available
    public static function getInstance()
    {
        if (self::$instance == null) {
            self::$instance = new SingleObject();
        }
        return self::$instance;
    }

    public function showMessage()
    {
        echo ("Hello World!\n");
    }

    //you can define methods that deal with private variables within this class
    // public function getConnection()
    // {
    //     return $this->conn;
    // }

    /*
    public function setname($new_name)
    {
        $this->namee = $new_name;
        return 0;
    }
    public function getname()
    {
        return $this->namee;
    }
    */
}
