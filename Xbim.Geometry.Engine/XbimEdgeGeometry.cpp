#include "XbimEdgeGeometry.h"

#include <BRepMesh_IncrementalMesh.hxx>
#include <Poly_PolygonOnTriangulation.hxx>
#include <Poly_Triangulation.hxx>
#include <TopLoc_Location.hxx>
#include <BRep_Tool.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <Geom_Circle.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <IntAna2d_AnaIntersection.hxx>
#include <GeomLib.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>
#include "XbimSolid.h"
#include "XbimEdgeSet.h"
#include "XbimCompound.h"
#include "XbimSolidSet.h"

using System::Runtime::InteropServices::Marshal;

using namespace  System::Threading;
using namespace  System::Linq;

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


namespace Xbim {
	namespace Geometry {
		void XbimEdgeGeometry::LogInfo(ILogger^ logger, Object^ entity, String^ format, ...array<Object^>^ arg)
		{
			String^ msg = String::Format(format, arg);
			IPersistEntity^ ifcEntity = dynamic_cast<IPersistEntity^>(entity);
			if (logger != nullptr)
			{

				if (ifcEntity != nullptr)
					LoggerExtensions::LogInformation(logger, "GeomEngine: #{0}={1} [{2}]", ifcEntity->EntityLabel, ifcEntity->GetType()->Name, msg);
				else
					if (entity == nullptr)
						LoggerExtensions::LogInformation(logger, "GeomEngine: [{0}]", msg);
					else
						LoggerExtensions::LogInformation(logger, "GeomEngine: {0} [{1}]", entity->GetType()->Name, msg);
			}
		}

		void XbimEdgeGeometry::LogWarning(ILogger^ logger, Object^ entity, String^ format, ...array<Object^>^ arg)
		{
			String^ msg = String::Format(format, arg);
			IPersistEntity^ ifcEntity = dynamic_cast<IPersistEntity^>(entity);
			if (logger != nullptr)
			{
				if (ifcEntity != nullptr)
					LoggerExtensions::LogWarning(logger, "GeomEngine: #{0}={1} [{2}]", ifcEntity->EntityLabel, ifcEntity->GetType()->Name, msg);
				else
					if (entity == nullptr)
						LoggerExtensions::LogWarning(logger, "GeomEngine: [{0}]", msg);
					else
						LoggerExtensions::LogWarning(logger, "GeomEngine: {0} [{1}]", entity->GetType()->Name, msg);
			}
		}

		void XbimEdgeGeometry::LogDebug(ILogger^ logger, Object^ entity, String^ format, ...array<Object^>^ arg)
		{
			String^ msg = String::Format(format, arg);
			IPersistEntity^ ifcEntity = dynamic_cast<IPersistEntity^>(entity);
			if (logger != nullptr)
			{
				if (ifcEntity != nullptr)
					LoggerExtensions::LogDebug(logger, "GeomEngine: #{0}={1} [{2}]", ifcEntity->EntityLabel, ifcEntity->GetType()->Name, msg);
				else
					if (entity == nullptr)
						LoggerExtensions::LogDebug(logger, "GeomEngine: [{0}]", msg);
					else
						LoggerExtensions::LogDebug(logger, "GeomEngine: {0} [{1}]", entity->GetType()->Name, msg);
			}
		}


		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdgeGeometry(XbimSolid^ xSolid) {
			//xBim solid derived from occshape -> compatible with BRepMesh_Incremental
			//BRepMesh_IncrementalMesh Mesh(xSolid, LinearDeflectionInMM, Standard_False, AngularDeflectionInRadians, Standard_False);

			//Computes Triangulation 
			//Mesh.Perform();

			//TopoDS_Shape

			//XbimEdge^ edge = gcnew XbimEdge();


			return xSolid->Edges;

		}

		void XbimEdgeGeometry::LogError(ILogger^ logger, Object^ entity, String^ format, ...array<Object^>^ arg)
		{
			String^ msg = String::Format(format, arg);
			IPersistEntity^ ifcEntity = dynamic_cast<IPersistEntity^>(entity);
			if (logger != nullptr)
			{
				if (ifcEntity != nullptr)
					LoggerExtensions::LogError(logger, "GeomEngine: #{0}={1} [{2}]", ifcEntity->EntityLabel, ifcEntity->GetType()->Name, msg);
				else
					if (entity == nullptr)
						LoggerExtensions::LogError(logger, "GeomEngine: [{0}]", msg);
					else
						LoggerExtensions::LogError(logger, "GeomEngine: {0} [{1}]", entity->GetType()->Name, msg);
			}
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcSweptDiskSolidPolygonal^ ifcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(ifcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcRevolvedAreaSolidTapered^ ifcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(ifcSolid, logger);
			return CreateEdgeGeometry(xSolid);

		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcFixedReferenceSweptAreaSolid^ ifcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(ifcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcAdvancedBrep^ ifcSolid, ILogger^ logger)
		{
			/*XbimCompound^ comp = gcnew XbimCompound((IIfcAdvancedBrep^)ifcSolid, logger);
			if (comp->Solids->Count > 0)
				XbimSolid^ xSolid =  comp->Solids->First;
			else
				XbimSolid^ xSolid =  gcnew XbimSolid();*/
			throw gcnew System::NotImplementedException();

		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcAdvancedBrepWithVoids^ ifcSolid, ILogger^ logger)
		{
			throw gcnew System::NotImplementedException();
			// TODO: insert return statement here
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcSectionedSpine^ ifcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(ifcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcSweptAreaSolid^ IIfcSolid, ILogger^ logger)
		{
			/*XbimSolid^ xSolid;
			IIfcExtrudedAreaSolid^ eas = dynamic_cast<IIfcExtrudedAreaSolid^>(IIfcSolid);
			if (eas != nullptr) return CreateEdge(eas, logger);
			IIfcRevolvedAreaSolid^ ras = dynamic_cast<IIfcRevolvedAreaSolid^>(IIfcSolid);
			if (ras != nullptr) return CreateEdge(ras, logger);
			IIfcSurfaceCurveSweptAreaSolid^ scas = dynamic_cast<IIfcSurfaceCurveSweptAreaSolid^>(IIfcSolid);
			if (scas != nullptr) return CreateEdge(scas, logger);*/
			throw gcnew NotImplementedException(String::Format("Swept Solid of Type {0} in entity #{1} is not implemented", IIfcSolid->GetType()->Name, IIfcSolid->EntityLabel));

		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcTriangulatedFaceSet^ shell, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(shell, logger);
			return CreateEdgeGeometry(xSolid);
		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcShellBasedSurfaceModel^ ifcSurface, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(ifcSurface, logger);
			return CreateEdgeGeometry(xSolid);

		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcFaceBasedSurfaceModel^ ifcSurface, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(ifcSurface, logger);
			return CreateEdgeGeometry(xSolid);

		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcExtrudedAreaSolid^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);

		};

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcRevolvedAreaSolid^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);

		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcSweptDiskSolid^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);

		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcBoundingBox^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);

		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcSurfaceCurveSweptAreaSolid^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcBooleanResult^ ifcSolid, ILogger^ logger)
		{
			throw gcnew System::NotImplementedException();
			// TODO: insert return statement here
		}
		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcBooleanClippingResult^ ifcSolid, ILogger^ logger)
		{
			throw gcnew System::NotImplementedException();
			// TODO: insert return statement here
		}


		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcHalfSpaceSolid^ IIfcSolid, ILogger^ logger)
		{

			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}


		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcBoxedHalfSpace^ IIfcSolid, ILogger^ logger)
		{

			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcPolygonalBoundedHalfSpace^ IIfcSolid, ILogger^ logger)
		{

			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}


		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcSphere^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcBlock^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcRightCircularCylinder^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcRightCircularCone^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcRectangularPyramid^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}

		IXbimEdgeSet^ XbimEdgeGeometry::CreateEdge(IIfcCsgPrimitive3D^ IIfcSolid, ILogger^ logger)
		{
			XbimSolid^ xSolid = gcnew XbimSolid(IIfcSolid, logger);
			return CreateEdgeGeometry(xSolid);
		}
	}

}

double __cdecl LoadEdgeGeometry(void)
{
	Xbim::Geometry::XbimEdgeGeometry^ gc = gcnew Xbim::Geometry::XbimEdgeGeometry();
	return gc->BooleanTimeOut;
}
