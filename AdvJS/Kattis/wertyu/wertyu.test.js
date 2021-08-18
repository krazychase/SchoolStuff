// WERTYU Test Program
// Chase Brown

const wertyu = require('./wertyu');

test('Return spaces', () => {
    expect(wertyu.wertyu(' ')).toBe(' ');
});

test('Return single shifted letter', () => {
    expect(wertyu.wertyu('W')).toBe('Q');
});

test('Return entire shifted string', () => {
    expect(wertyu.wertyu('JR;;P EPT;F')).toBe('HELLO WORLD');
});