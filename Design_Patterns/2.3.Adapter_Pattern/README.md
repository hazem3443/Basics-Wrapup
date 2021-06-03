# Adapter Pattern

Adapter pattern works as a bridge between two incompatible interfaces.
This pattern involves a single class which is responsible to join functionalities of independent or incompatible interfaces. A real life example could be a case of card reader which acts as an adapter between memory card and a laptop. You plugin the memory card into card reader and card reader into the laptop so that memory card can be read via laptop.

We are demonstrating use of Adapter pattern via following example in which an audio player device can play mp3 files only and wants to use an advanced audio player capable of playing vlc and mp4 files.

## Implementation

We have a __MediaPlayer__ interface and a concrete class __AudioPlayer__ implementing the __MediaPlayer__ interface. __AudioPlayer__ can play mp3 format audio files by default.

We are having another interface __AdvancedMediaPlayer__ and concrete classes implementing the __AdvancedMediaPlayer__ interface. These classes can play vlc and mp4 format files.

We want to make __AudioPlayer__ to play other formats as well. To attain this, we have created an adapter class __MediaAdapter__ which implements the __MediaPlayer__ interface and uses __AdvancedMediaPlayer__ objects to play the required format.

__AudioPlayer__ uses the adapter class __MediaAdapter__ passing it the desired audio type without knowing the actual class which can play the desired format. __AdapterPatternDemo__, our demo class will use __AudioPlayer__ class to play various formats.

![Adapter Pattern UML diagram](https://www.tutorialspoint.com/design_pattern/images/adapter_pattern_uml_diagram.jpg)
