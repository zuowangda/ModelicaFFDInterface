within ;
package DllTest "Test package for dll"
  function Initiate "Start the FFD"
  external"C" initiateFFD();
    annotation (Include="#include <interface_ffd.h>", Library="ModelicaFFD");
  end Initiate;

  model ChangeDll
  Real x;
  initial equation
    DllTest.Initiate();
  equation
    x = time;
    DllTest.change();
     annotation ();
  end ChangeDll;

  function change "change the variable in salve"
  external"C" exchangeData();
    annotation (Include="#include <interface_ffd.h>", Library="ModelicaFFD");
  end change;
  annotation (uses(Modelica(version="3.2")));
end DllTest;
