// Backspace Kattis Problem
// Chase Brown

const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function backspace(data)
{
    output = [];
    for (var i = 0; i < data.length; i++)
    {
        if(data[i] == '<')
        {
            output.pop();
        }
        else
        {
            output.push(data[i]);
        }
    }
    return output.join('');
}

function solve()
{
    rl.on('line', (line) => {
        var answer = backspace(line);
        console.log(answer);
    });
}

if (require.main == module) {
    solve();
}

module.exports = { backspace: backspace };