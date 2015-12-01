This is an Arduino library for simplifying and unifying software tracing.
The main default tracing output is still Serial interface, but it is configurable.
All trace method is required to provide the level. This mechanism allow to track whether there is any error took place while executing. In case of error constant LED13 blinking is enabled by default using internal timer.
Also LED13 can be used for additional output of numbers or scale.