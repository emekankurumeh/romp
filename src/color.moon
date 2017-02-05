-- CONTROL --
--  "\27[0m" reset
--  "\27[1m" bold
--  "\27[2m" dim
--  "\27[4m" underlined
--  "\27[5m" blinking
--  "\27[7m" inverted
--  "\27[8m" hidden

-- FOREGROUND COLOR --
--  "\27[30m" black
--  "\27[31m" red
--  "\27[32m" green
--  "\27[33m" yellow
--  "\27[34m" blue
--  "\27[35m" pink
--  "\27[36m" cyan
--  "\27[37m" white
--  "\27[38;5;0m..255m" extended foreground color
--  "\27[38;2;r;b;gm" extended foreground color r,g,b are 0..255

-- BACKGROUND COLOR --
--  "\27[40m" black background
--  "\27[41m" red background
--  "\27[42m" green background
--  "\27[43m" yellow background
--  "\27[44m" blue background
--  "\27[45m" pink background
--  "\27[46m" cyan background
--  "\27[47m" white background
--  "\27[48;5;0m..255m" extended background color
--  "\27[48;2;r;b;gm" extended background color r,g,b are 0..255

-- LIGHT FOREGROUND COLOR --
--  "\27[90m" light black
--  "\27[91m" light red
--  "\27[92m" light green
--  "\27[93m" light yellow
--  "\27[94m" light blue
--  "\27[95m" light pink
--  "\27[96m" light cyan
--  "\27[97m" light white

-- LIGHT BACKGROUND COLOR --
--  "\27[100m" light black background
--  "\27[101m" light red background
--  "\27[102m" light green background
--  "\27[103m" light yellow background
--  "\27[104m" light blue background
--  "\27[105m" light pink background
--  "\27[106m" light cyan background
--  "\27[107m" light white background

-- MISC --
-- "\27[...;_m" any combination ie. "\27[5;35;7m"

{
  reset: "\27[0m"
  bold: "\27[1m"
  dim: "\27[2m"
  underline: "\27[4m"
  blink: "\27[5m"
  invert: "\27[7m"
  hide: "\27[8m"
  fore:
    black: "\27[30m"
    red: "\27[31m"
    green: "\27[32m"
    yellow: "\27[33m"
    blue: "\27[34m"
    pink: "\27[35m"
    cyan: "\27[36m"
    white: "\27[37m"
    light:
      black: "\27[90m"
      red: "\27[91m"
      green: "\27[92m"
      yellow: "\27[93m"
      blue: "\27[94m"
      pink: "\27[95m"
      cyan: "\27[96m"
      white: "\27[97m"
  back:
    black: "\27[40m"
    red: "\27[41m"
    green: "\27[42m"
    yellow: "\27[43m"
    blue: "\27[44m"
    pink: "\27[45m"
    cyan: "\27[46m"
    white: "\27[47m"
    light:
      black: "\27[100m"
      red: "\27[101m"
      green: "\27[102m"
      yellow: "\27[103m"
      blue: "\27[104m"
      pink: "\27[105m"
      cyan: "\27[106m"
      white: "\27[107m"
  -- MISC --
  -- "\27[38;5;0m..255m" extended foreground color
  -- "\27[38;2;r;b;gm" extended foreground color r,g,b are 0..255
  -- "\27[48;5;0m..255m" extended background color
  -- "\27[48;2;r;b;gm" extended background color r,g,b are 0..255
  -- "\27[...;_m" any combination ie. "\27[5;35;7m"
}
