with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;
use Countdown;

package Data is
  type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

  countdown: Countdown(4);

  function Func(MH, MK, ML: Integer_Matrix) return Integer;
  procedure Mult_Part(MH, MK, tmp: Integer_Matrix; start, end: Integer);

end Data;
