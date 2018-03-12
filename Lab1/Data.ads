with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

package Data is
  type Integer_Vector is array (Positive range <>) of Integer;
  type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

  awaitSum: Suspension_Object;
  awaitMax: Suspension_Object;
  awaitMult: Suspension_Object;
  awaitResult: Suspension_Object;

  function Func(A, B, C: Integer_Vector; MA, ME: Integer_Matrix) return Integer_Matrix;
  procedure Put_Matrix(M: Integer_Matrix);
end Data;
