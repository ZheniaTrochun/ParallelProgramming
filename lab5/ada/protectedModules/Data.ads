with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;
with CountdownPackage;
use CountdownPackage;

package Data is

  type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

  countdown: CountdownPackage.Countdown(4);

  tmp: Integer_Matrix(1 .. 10, 1 .. 10);

  function Func(MH, MK, ML: Integer_Matrix) return Integer;
  procedure Mult_Part(MH, MK: Integer_Matrix; start, finish: Integer);

end Data;
