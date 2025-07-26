# Worms
A reimplementation of Worms? for modern terminals.


This video: 

"Vibe Coding"
https://www.youtube.com/watch?v=1OxBv9Q7Uxo

Led to the following chain of URLs:

Langton's ant
https://en.wikipedia.org/wiki/Langton%27s_ant

Turmite
https://en.wikipedia.org/wiki/Turmite

Paterson's worms
https://en.wikipedia.org/wiki/Paterson%27s_worms

Worms?
https://en.wikipedia.org/wiki/Worms%3F

Worms? for Atari 8-bit teaches us about Atari automata | Atari A to Z 
https://www.youtube.com/watch?v=VZ0n1kMPYrE

Looking at the game board, I realized it could be replicated almost exactly using ASCII art, in a modern terminal. 

In an attempt to replicate the AUTO worm encoding, I found these resources:

EA Worms? source code (Forth)
https://forums.atariage.com/topic/318960-ea-worms-source-code-forth/

Source code for Worms? by David S. Maynard from his original floppies, available for the Atari 8-bit and Commodore 64.
https://github.com/savetz/worms

David Maynard Worms? Development Notes
https://archive.org/details/david-maynard-worms-development-notes

Unfortunately, the source code looked too much like assembly language for me to understand how to rewrite the behavior in C++. 
I figured I could write out such a set of codes by looking through the list of path images and picking paths that are open, 
before recalling that I already implemented RAND mode to do that autonomously. 


In summary, each (colored) worm has an encoded list of which path to take given what paths are active or deactivated around its position. 
These can be programmed in during gameplay, or copy-pasted into the worms.txt file. 
