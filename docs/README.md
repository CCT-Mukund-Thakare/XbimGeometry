## Xbim Geometry Exploration

- [Xbim Geometry Exploration](#xbim-geometry-exploration)
  - [Case Study IXbimGeometryEngine Interface](#case-study-ixbimgeometryengine-interface)
    - [How the IXbimGeometryEngine Interface is defined](#how-the-ixbimgeometryengine-interface-is-defined)
    - [How XbimGeometryEngine calls the Native C++ Code](#how-xbimgeometryengine-calls-the-native-c-code)
    - [How We Have Added a Custom Functionality to Extract Edges](#how-we-have-added-a-custom-functionality-to-extract-edges)
  - [Adding New Classes to Xbim.Geometry.Engine Project](#adding-new-classes-to-xbimgeometryengine-project)
  - [Building XbimEssentials Project](#building-xbimessentials-project)
  - [Packaging the XbimEssentials Project](#packaging-the-xbimessentials-project)
  - [Building XbimGeometry Project](#building-xbimgeometry-project)
  - [Packaging XbimGeometry Project](#packaging-xbimgeometry-project)
  - [Testing, Debugging, and Profiling Geometry Engine Projects](#testing-debugging-and-profiling-geometry-engine-projects)
  - [Using the Generated Packages in Another Project](#using-the-generated-packages-in-another-project)
  - [Risks](#risks)
  - [Additional Resources and References](#additional-resources-and-references)

### Case Study IXbimGeometryEngine Interface

#### How the IXbimGeometryEngine Interface is defined

1. The IXbimGeometryEngine Interface is defined in Xbim.Essentials.Ifc4 Module
2. IXbimGeometryEngine Interface is Implemented Xbim.Geometry.Engine.Interop > XbimGeometryEngine.cs Project as a Wrapper for the Native Code
3. XbimGeometryEngine class defined in XbimGeometryEngine.cs internally calls the Functions defined in Xbim.Geometry.Engine (Native C++ Project) which uses OCCT Code
4. Both XbimGeometryEngine classes defined in C# and C++ derive from the IXbimGeometryEngine interface defined in Xbim.Essentials.Ifc4 Module.

#### How XbimGeometryEngine calls the Native C++ Code

1. The XbimGeometryEngine's Constructor loads the Xbim.GeometryEngine32.dll or Xbim.GeometryEngine64.dll depending upon the platform architecture (x86 or x64)
2. It grabs the function XbimGeometryEngine class defined in native code and then creates an instance of it
3. To call the methods defined in the XbimGeometry's instance created loaded from the dll it has to be cast as IXbimGeometryEngine
4. This is why both XbimGeometryEngine classes defined in C# and C++ are derived from a Common Interface. If they don't implement the same interface the instance created at runtime cannot access the methods.
5. All the calls made to XbimGeometryEngine C# code then call the native methods defined in C++ through the instance loaded through the dll.

#### How We Have Added a Custom Functionality to Extract Edges

1. Add an Inteface called IXbimEdgeGeometry in Xbim.Essetials.Ifc4 Module
2. Build the Xbim.Essentials Project with the new IXbimEdgeGeometry interface and create custom packages
3. Import the Custom Packages in Xbim.Geometry Project
4. Add a class called XbimEdgeGeometry in Xbim.Geometry.Engine.Interop Project which **implements** Xbim.Essentials.Ifc4.IXbimEdgeGeometry interface
5. The XbimEdgeGeometry class has a member variable of type IXbimEdgeGeometry which will be used to acess native code loaded from the dll at runtime
6. Add a class called XbimEdgeGeometry in Xbim.Geometry.Engine which **extends** from Xbim.Essentials.Ifc4.IXbimEdgeGeometry and implement all the methods defined in the interface. Use OCCT to extract edges.
7. The Xbim.Geometry.Engine.Interop.XbimEdgeGeometry class then loads the Xbim.Geometry.Engine.XbimEdgeGeometry class from dll at runtime to access its functionality.
8. The Xbim.Geometry.Engine.Interop.XbimEdgeGeometry is just a wrapper class that forwards the calls to native code using OCCT.
9. Build the XbimGeometry and XbimEssentials Solutions and generate new packages
10. Install the newly generated packages into another project to use the new functionality.- [Xbim Geometry Exploration](#xbim-geometry-exploration)

- [Xbim Geometry Exploration](#xbim-geometry-exploration)
  - [Case Study IXbimGeometryEngine Interface](#case-study-ixbimgeometryengine-interface)
    - [How the IXbimGeometryEngine Interface is defined](#how-the-ixbimgeometryengine-interface-is-defined)
    - [How XbimGeometryEngine calls the Native C++ Code](#how-xbimgeometryengine-calls-the-native-c-code)
    - [How We Have Added a Custom Functionality to Extract Edges](#how-we-have-added-a-custom-functionality-to-extract-edges)
  - [Adding New Classes to Xbim.Geometry.Engine Project](#adding-new-classes-to-xbimgeometryengine-project)
  - [Building XbimEssentials Project](#building-xbimessentials-project)
  - [Packaging the XbimEssentials Project](#packaging-the-xbimessentials-project)
  - [Building XbimGeometry Project](#building-xbimgeometry-project)
  - [Packaging XbimGeometry Project](#packaging-xbimgeometry-project)
  - [Testing, Debugging, and Profiling Geometry Engine Projects](#testing-debugging-and-profiling-geometry-engine-projects)
  - [Using the Generated Packages in Another Project](#using-the-generated-packages-in-another-project)
  - [Risks](#risks)
  - [Additional Resources and References](#additional-resources-and-references)

### Adding New Classes to Xbim.Geometry.Engine Project

1. Right-click on the Xbim.Geometry.Engine Project in Visual Studio
2. Select Add from the Dropdown Menu
3. Create a .cpp and .h file
4. Right Click on the .cpp file and select properties
5. Go to C/C++ Section
6. Make Sure the **Common Language Runtime Support Option** is set to **Common Language Runtime Support (/clr)** otherwise the build will throw fatal errors if any C# Interop Code is Used in the File.

### Building XbimEssentials Project

1. Clone the XbimEssentials repo from [XbimEssentials](https://github.com/CCT-Mukund-Thakare/XbimEssentials)
2. Switch to Branch [issues/issue465](https://github.com/CCT-Mukund-Thakare/XbimEssentials/tree/issues/issue465)
3. Open the Solution using Visual Studio
4. Build the Solution (It will build 9 Projects)

### Packaging the XbimEssentials Project

1. After Successfully building the projects, right-click on the Project and Select the **Pack** option from the dropdown menu
2. Selecting the **Pack** option will generate a .nuget package with **version 5.1.341** e.g (Xbim.Common.5.1.341.nupkg)
3. Do this for all the Projects (Ignore the Test Projects)
4. **Make Sure to Build the Packages in Release Mode**
5. Go to Project Root Folder (C:\workspace\Xbim\XbimEssentials)
6. Search for .nupkg in the Search Bar. It will return all the packages
7. Copy all the Packages and place them in a new Folder called packages

### Building XbimGeometry Project

1. Clone the XbimGeometry repo from [XbimGeometry](https://github.com/CCT-Mukund-Thakare/XbimEssentials)
2. Switch to Branch [issues/issue465](https://github.com/CCT-Mukund-Thakare/XbimGeometry/tree/issues/issue465)
3. Open the Solution using Visual Studio
4. It will restore the required packages from nuget.org instead of our custom packages
5. Go Project > Manage Nuget Packages
6. Click on the Settings Icon on the Right Most Corner next to Package Sources. It will open up the menu to configure package sources
7. Click on the + Sign to Add a new Package Source and Set the Path to the new Package Folder created while building XbimEssential packages (See Packaging XbimEssentials Project Step 7)
8. Uncheck the nuget.org as  Package Source in the Config Menu.
9. Go to C:\Users\\{UserName}\\.nuget\packages and remove all the xbim packages
10. Restart Visual Studio
11. New Custom Packages are restored from the local source created in Building XbimGeometry Project > Step 7
12. Build the Xbim.Geometry.Engine.Interop Project First and then build the rest of the projects
13. **Directly Building the Solution May Fail and Throw a Lot of Errors**

### Packaging XbimGeometry Project

1. Once all the Projects are Built, Right Click on the **C#** Projects and Click on **Pack** from the dropdown menu to generate the nuget packages (Ignore the Regression and Tests Projects). It will generate a nupkg file with **version 5.1.437**
2. Place the generated packages into the local package folder.

### Testing, Debugging, and Profiling Geometry Engine Projects

1. To Test, Debug, or Profile the Xbim.Geometry.Engine and Xbim.Geometry.Engine.Interop projects use the **Xbim.Regression** Project
2. Modify the **Xbim.Regression > Program.cs** and add custom logic to test and debug the changes

### Using the Generated Packages in Another Project

1. Follow the Steps mentioned in Building Xbim Geometry Project to add a Custom Package Source for nuget packages.
2. Install the Custom Packages from the Local folder to use the custom functionality in another project

### Risks

1. Difficult to Maintain the Custom Packages
2. Need to Push the Packages on some remote source to reduce a few steps while building the projects.
3. The Current Solution is based on XbimGeometry 5.1.437 and XbimEssentials 5.1.341 which no longer contain the latest changes. These Projects have been migrated to netcore version 6.0

### Additional Resources and References

1. [Xbim Ticket](https://github.com/xBimTeam/XbimGeometry/issues/465)
2. [Quick-C-CLI-Learn-C-CLI-in-less-than-10-minutes](https://www.codeproject.com/Articles/19354/Quick-C-CLI-Learn-C-CLI-in-less-than-10-minutes)
3. [How Geometry is Created with OCC](https://dev.opencascade.org/doc/refman/html/class_b_rep_prim_a_p_i___make_prism.html)
4. [Xbim Toolkit Overview](https://github.com/xBimTeam/XbimEssentials?tab=readme-ov-file#toolkit-overview)
5. [Open Cascade CAD Assistant Viewer](https://www.opencascade.com/products/cad-assistant/)
