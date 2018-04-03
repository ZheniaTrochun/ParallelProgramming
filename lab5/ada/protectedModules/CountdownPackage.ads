package CountdownPackage is

  protected type Countdown (Start_Count : Integer := 1) is

      entry Secure;
      procedure Release;
      function Count return Integer;

  private
      Current_Count : Integer := Start_Count;

  end;
end CountdownPackage;
