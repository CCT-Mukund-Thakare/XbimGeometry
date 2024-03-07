#include "XbimVertex.h"
#include "XbimVertex.h"
#include "XbimEdge.h"
#include "XbimSolid.h"

using namespace System;
using namespace Xbim::Common::Geometry;
using namespace System::Collections::Generic;
using namespace Xbim::Ifc4::Interfaces;
using namespace Xbim::Ifc4;
using namespace Microsoft::Extensions::Logging;

using namespace System;
using namespace System::IO;
using namespace Xbim::Common;
using namespace Xbim::Common::Geometry;

using namespace System::Configuration;
using namespace System::Reflection;

__declspec(dllexport) double __cdecl LoadEdgeGeometry(void);


namespace Xbim {
	namespace Geometry {

		ref class XbimEdgeGeometry : IXbimEdgeGeometry {


		private:
			static XbimEdgeGeometry()
			{
				//AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(ResolveHandler);
				/*Assembly::Load("Xbim.Ifc4");
				Assembly::Load("Xbim.Common");
				Assembly::Load("Xbim.Tessellator");*/

				String^ timeOut = ConfigurationManager::AppSettings["BooleanTimeOut"];
				if (!int::TryParse(timeOut, BooleanTimeOut))
					BooleanTimeOut = 60;
				String^ fuzzyString = ConfigurationManager::AppSettings["FuzzyFactor"];
				if (!double::TryParse(fuzzyString, FuzzyFactor))
					FuzzyFactor = 10;

				String^ linearDeflection = ConfigurationManager::AppSettings["LinearDeflectionInMM"];
				if (!double::TryParse(linearDeflection, LinearDeflectionInMM))
					LinearDeflectionInMM = 50; //max chord diff

				String^ angularDeflection = ConfigurationManager::AppSettings["AngularDeflectionInRadians"];
				if (!double::TryParse(angularDeflection, AngularDeflectionInRadians))
					AngularDeflectionInRadians = 0.5;// deflection of 28 degrees

				String^ ignoreIfcSweptDiskSolidParamsString = ConfigurationManager::AppSettings["IgnoreIfcSweptDiskSolidParams"];
				if (!bool::TryParse(ignoreIfcSweptDiskSolidParamsString, IgnoreIfcSweptDiskSolidParams))
					IgnoreIfcSweptDiskSolidParams = false;

			}

		public:

			static String^ SurfaceOfLinearExtrusion = "#SurfaceOfLinearExtrusion";
			static String^ PolylineTrimLengthOneForEntireLine = "#PolylineTrimLengthOneForEntireLine";

			static Assembly^ ResolveHandler(Object^ /*Sender*/, ResolveEventArgs^ /*args*/)
			{

				// Warning: this should check the args for the assembly name!
				return nullptr;
			}

		protected:
			~XbimEdgeGeometry()
			{
			}

		public:
			static void LogInfo(ILogger^ logger, Object^ entity, String^ format, ... array<Object^>^ arg);
			static void LogWarning(ILogger^ logger, Object^ entity, String^ format, ... array<Object^>^ arg);
			static void LogError(ILogger^ logger, Object^ entity, String^ format, ... array<Object^>^ arg);
			static void LogDebug(ILogger^ logger, Object^ entity, String^ format, ... array<Object^>^ arg);

			static int BooleanTimeOut;
			static double FuzzyFactor;
			static double LinearDeflectionInMM;
			static double AngularDeflectionInRadians;
			static bool IgnoreIfcSweptDiskSolidParams;

			virtual IXbimEdgeSet^ CreateEdgeGeometry(XbimSolid^ xSolid);
			virtual IXbimEdgeSet^ CreateEdge(IIfcExtrudedAreaSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcSweptAreaSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcRevolvedAreaSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcSweptDiskSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcBoundingBox^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcSurfaceCurveSweptAreaSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcBooleanResult^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcBooleanClippingResult^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcHalfSpaceSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcPolygonalBoundedHalfSpace^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcBoxedHalfSpace^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcTriangulatedFaceSet^ shell, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcShellBasedSurfaceModel^ ifcSurface, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcFaceBasedSurfaceModel^ ifcSurface, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcCsgPrimitive3D^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcSphere^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcBlock^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcRightCircularCylinder^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcRightCircularCone^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcRectangularPyramid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcSweptDiskSolidPolygonal^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcRevolvedAreaSolidTapered^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcFixedReferenceSweptAreaSolid^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcAdvancedBrep^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcAdvancedBrepWithVoids^ ifcSolid, ILogger^ logger);
			virtual IXbimEdgeSet^ CreateEdge(IIfcSectionedSpine^ ifcSolid, ILogger^ logger);

		};
	}
}