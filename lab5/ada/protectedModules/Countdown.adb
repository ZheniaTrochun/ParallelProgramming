package CountdownPackage is

  protected type Countdown (Start_Count : Integer := 1) is

      entry Secure;
      procedure Release;
      function Count return Integer;

  private
      Current_Count : Integer := Start_Count;

  end;


  protected body Contdown is

      entry Secure when Current_Count = 0 is
      begin
          Current_Count := Current_Count - 1;
      end;

      procedure Release is
      begin
          Current_Count := Current_Count - 1;
      end;

      function Count return Integer is
      begin
          return Current_Count;
      end;

  end Countdown;
end CountdownPackage;
