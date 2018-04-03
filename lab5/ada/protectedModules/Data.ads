with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;
with CountdownPackage;

package Data is

  type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

  countdown: CountdownPackage.Countdown(4);

  function Func(MH, MK, ML: Integer_Matrix) return Integer;
  procedure Mult_Part(MH, MK, tmp: Integer_Matrix; start, until: Integer);

end Data;
