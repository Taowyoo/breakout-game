## Breakout - Part 3

<img align="right" width="150px" src="./Media/Nolan_Bushnell_2013.jpg">
Ship it! Nolan has given you the greeenlight. As the game testers(i.e. your friends/roommates/etc) help you take care of the final bugs and pass Quality Assurance testing there are only a few steps left before your game goes from the beta build to the final version!

## Step 1 - Documentation
While Nolan has given the greenlight, he wants to ensure the code is wrapped up. Nolan has required using 'Doxygen' <a href="http://www.doxygen.nl/">(Doxygen webpage)</a> or [Doxypress](https://www.copperspice.com/documentation-doxypress.html) to document the source code and automatically generate .html pages. 

**Your documentation should cover your classes and functions.**

An example of a well documented probjects using doxygen can be found here:

- https://www.ogre3d.org/docs/api/1.9/
- http://www.horde3d.org/docs/html/_api.html

### Doxygen style comments

Some examples of documentation are listed here: http://www.doxygen.nl/manual/docblocks.html A helpful tool to use may be: [Doxywizard](http://www.doxygen.nl/manual/doxywizard_usage.html)

Comments within code are in the style of:

```cpp
/*!
 * ... text ...
 */

/*!
 ... text ...
*/

//!
//!... text ...
//!

/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */

```

## Step 2 - Build (binary file) **DONE**
You need to have a compiled binary of your game for your operating system (Either Windows, Mac, or Linux). You can assume a target audience of either a 64-bit Mac, Ubuntu Linux, or a Windows 10 machine. There should additionally be instructions about how to compile your code from source. The compilation should be trivial (running `python build.py` for example, or listing a series of `apt-get install` in a single command or a script you have built. **Make it trivial** so customers/TA's can easily build your project :) ).

## Step 3 - Post mortem
A post mortem in games is a look back at what could be improved. Write a brief (2-3 paragraphs) on what could be improved if you had an additional 8 weeks to work on this project. Where would you allocate time, what tools would you build, would you use any different tools, etc.

There are so many places I could improve.

1. About code:
   1. There is a double free bug when close the game, I am going to fix it, even it does no infuence on game play.
   2. Related to last problem. I should think more deep and consider to refactor the `ResourceManager`. There are so many memory related points I have to carefully deal with.
   3. There are some code style inconsistancy because of quick development. I will improve them later.
   4. The doc & comments are still not quite well.
   5. The overall design of each component can be improved. As many classes were written before think and just made sure the functionality of each class.
2. About gameplay:
   1. The Collision detect and Collision type detect still has some bug on some side cases.
   2. I could add some more feature of gameplay, such as: following buffs or ball speed chang.
   3. Add mouse control will be one great improvement to game.
3. About outlooking:
   1. The outlooking is so simple, I did not use any texture. I should consider to improve the game scene and bricks with some colorful textures.
4. About Audio and other:
   1. I should make a menu for the game, so that player can make more change on game settings: Such as change background music.

## Step 4 - Website

Your documentation, a link to your binary, and your brief post mortem should be put together on a 1-page .html page. 

Additionally, provide a 1 minute video trailer followed by at least 3 screenshots of your game (order matters, video first, then screenshots below). This website will be the first place I look to grab your project files and binaries. 

[Link](https://taowyoo.github.io/post/breakout-game/)

**Note**: I think it is incredibly important to build a portfolio of your game development works! You can re-use this template for your next project, and potentially other personal projects.
