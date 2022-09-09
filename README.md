# Anti Bevel Gear Contingent
A moment of silence for the deceased...

## PROS
Instead of using Vexcode, we are using [PROS](https://pros.cs.purdue.edu/). This is for compatibility with Linux mostly and also it has some other benefits compared to using vexcode while being competition legal. 

## Code guidelines
1. All code will be written in PROS
2. Code will be available with edit history on GitHub
3. Any changes to the code should be pushed online ASAP
4. Always `git pull` before editing code
5. Make a release for the code on the robot before each competition
6. All commits should be pasted into the Engineering Notebook
    - Email notifications for GitHub should be on to monitor and paste commits into the notebook at the correct time

## Setting up this code
### Requirements
1. You probably want to be using Linux or WSL for this (I found fedora is the best to use)
2. `git`, `python3`, `pros-cli` (from pip), `arm-none-eabi-g++`, and if you get errors try installing `arm-none-eabi-newlib`
3. Use pros to make a new project with `pros conductor new-project <location>`
4. CD into `src/` inside the new project and delete anything inside
5. Use `git clone https://github.com/Team-DLOW/2022` to download the code and log in to git on your computer
6. There is no step 6, you are now ready to edit and collaborate on code correctly!

### Using VSCODE
Visual Studio Code is a pretty great ide and PROS has a extension for it to make it really easy to program through it. Just install PROS through the extension store and follow all the on screen prompts and install everything it asks for. Now you can click the pros icon in the top right to build and upload code to the robot with ease!
