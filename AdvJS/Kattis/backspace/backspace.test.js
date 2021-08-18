// Backspace Test Program
// Chase Brown

const bs = require('./backspace');

test('No backspaces', () => {
    expect(bs.backspace('helloworld')).toBe('helloworld');
});

test('All backspaces', () => {
    expect(bs.backspace('123456789<<<<<<<<<')).toBe('');
});

test('Mixed backspaces', () => {
    expect(bs.backspace('chh<aa<ss<s<eee<<')).toBe('chase');
});
