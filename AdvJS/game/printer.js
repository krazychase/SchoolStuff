// Chase Brown
// Print module for game.js

const { builtinModules } = require("module");

function printTitle()
{
    console.log(' _   _ ');
    console.log('| | | |');
    console.log('| |_| | __ _ _ __   __ _ _ __ ___   __ _ _ __');
    console.log('|  _  |/ _` | \'_ \\ / _` | \'_ ` _ \\ / _` | \'_ \\ ');
    console.log('| | | | (_| | | | | (_| | | | | | | (_| | | | |');
    console.log('\\_| |_/\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|');
    console.log('                    __/ |')
    console.log('                   |___/')
}

function printGallows(fails, word)
{
    if (fails == 0)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /       / \\         ');
        console.log('| |/       (___)        ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|');
    }
    else if (fails == 1)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /     ( 0o0 )         ');
        console.log('| |/                    ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|');
    }
    else if (fails == 2)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /     ( 0o0 )         ');
        console.log('| |/         |           ');
        console.log('| |          |           ');
        console.log('| |          |           ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|');
    }
    else if (fails == 3)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /     ( 0o0 )         ');
        console.log('| |/         |           ');
        console.log('| |         /|           ');
        console.log('| |        / |           ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|'); 
    }      
    else if (fails == 4)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /     ( 0o0 )         ');
        console.log('| |/         |           ');
        console.log('| |         /|\\           ');
        console.log('| |        / | \\         ');
        console.log('| |                     ');
        console.log('| |                     ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|');  
    }     
    else if (fails == 5)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /     ( 0o0 )         ');
        console.log('| |/         |           ');
        console.log('| |         /|\\           ');
        console.log('| |        / | \\         ');
        console.log('| |         /           ');
        console.log('| |        /             ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|'); 
    }      
    else if (fails == 6)
    {
        console.log('_______________________ ');
        console.log('| _____________________|');
        console.log('| |  /      | |         ');
        console.log('| | /     ( XoX )         ');
        console.log('| |/         |           ');
        console.log('| |         /|\\           ');
        console.log('| |        / | \\         ');
        console.log('| |         / \\          ');
        console.log('| |        /   \\          ');
        console.log('| |_____________________');
        console.log('|                       |');
        console.log('|_______________________|');
        console.log('\n' + word);
        console.log(' _____   ___  ___  ___ _____ _____  _   _ ___________ ');
        console.log('|  __ \\ / _ \\ |  \\/  ||  ___|  _  || | | |  ___| ___ \\');
        console.log('| |  \\// /_\\ \\| .  . || |__ | | | || | | | |__ | |_/ /');
        console.log('| | __ |  _  || |\\/| ||  __|| | | || | | |  __||    / ');
        console.log('| |_\\ \\| | | || |  | || |___\\ \\_/ /\\ \\_/ / |___| |\\ \\ ');
        console.log(' \\____/\\_| |_/\\_|  |_/\\____/ \\___/  \\___/\\____/\\_| \\_|');
    }
}

function winner(word)
{
    console.log('\n' + word);
    console.log('__   __          _    _ _    ');
    console.log('\\ \\ / /         | |  | (_)     ');
    console.log(' \\ V /___  _   _| |  | |_ _ __  ');
    console.log('  \\ // _ \\| | | | |/\\| | | \'_ \\ ');
    console.log('  | | (_) | |_| \\  /\\  / | | | |');
    console.log('  \\_/\\___/ \\__,_|\\/  \\/|_|_| |_|');
}

module.exports = {printTitle, printGallows, winner}