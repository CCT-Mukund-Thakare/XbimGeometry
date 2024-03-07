using System;
using System.IO;
using System.Reflection;
using Microsoft.Extensions.Logging;


using Xbim.Common;
using Xbim.Common.Geometry;
using Xbim.Ifc4.Interfaces;
using Xbim.Ifc4;

namespace Xbim.Geometry.Engine.Interop
{

    namespace Xbim.Geometry.Engine.Interop
    {

        public class XbimEdgeGeometry : IXbimEdgeGeometry
        {
            private readonly IXbimEdgeGeometry _engine;
            private readonly ILogger<XbimEdgeGeometry> _logger;
            static XbimEdgeGeometry()
            {

                // We need to wire in a custom assembly resolver since Xbim.Geometry.Engine is 
                // not located using standard probing rules (due to way we deploy processor specific binaries)
                AppDomain.CurrentDomain.AssemblyResolve += XbimCustomAssemblyResolver.ResolverHandler;
            }

            public XbimEdgeGeometry() : this(null)
            {

            }


            public XbimEdgeGeometry(ILogger<XbimEdgeGeometry> logger)
            {

                // Warn if runtime for Engine is not present, this is not necessary any more as we are net472
                //XbimPrerequisitesValidator.Validate();


                _logger = logger ?? XbimLogging.CreateLogger<XbimEdgeGeometry>();

                var conventions = new XbimArchitectureConventions();    // understands the process we run under
                string assemblyName = $"{conventions.ModuleName}.dll";// + conventions.Suffix; dropping the use of a suffix
                _logger.LogDebug("Loading {assemblyName}", assemblyName);
                try
                {
                    var ass = Assembly.Load(assemblyName);
                    _logger.LogTrace("Loaded {fullName} from {codebase}", ass.GetName().FullName, ass.CodeBase);
                    var t = ass.GetType("Xbim.Geometry.XbimEdgeGeometry");
                    var obj = Activator.CreateInstance(t);
                    _logger.LogTrace("Created Instance of {fullName}", obj.GetType().FullName);
                    if (obj == null)
                    {
                        throw new Exception("Failed to create Geometry Engine");
                    }

                    _engine = obj as IXbimEdgeGeometry;

                    if (_engine == null)
                    {
                        throw new Exception("Failed to cast Geometry Engine to IXbimGeometryEngine");
                    }

                    _logger.LogDebug("XbimGeometryEngine constructed successfully");
                }
                catch (Exception e)
                {
                    _logger.LogError(0, e, "Failed to construct XbimGeometryEngine");
                    throw new FileLoadException($"Failed to load Xbim.Geometry.Engine{conventions.Suffix}.dll", e);
                }

            }

            public IXbimEdgeSet CreateEdge(IIfcBoundingBox ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcSweptDiskSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcShellBasedSurfaceModel ifcSurface, ILogger logger)
            {
                return _engine.CreateEdge(ifcSurface, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcSurfaceCurveSweptAreaSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcBoxedHalfSpace ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcPolygonalBoundedHalfSpace ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcHalfSpaceSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcFaceBasedSurfaceModel ifcSurface, ILogger logger)
            {
                return _engine.CreateEdge(ifcSurface, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcTriangulatedFaceSet shell, ILogger logger)
            {
                return _engine.CreateEdge(shell, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcSweptAreaSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcExtrudedAreaSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcCsgPrimitive3D ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcSphere ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcBlock ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcRightCircularCylinder ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcRevolvedAreaSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcRectangularPyramid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcRightCircularCone ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcRevolvedAreaSolidTapered ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcFixedReferenceSweptAreaSolid ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcAdvancedBrep ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcAdvancedBrepWithVoids ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcSectionedSpine ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }

            public IXbimEdgeSet CreateEdge(IIfcSweptDiskSolidPolygonal ifcSolid, ILogger logger)
            {
                return _engine.CreateEdge(ifcSolid, logger);
            }
        }
    }
}
