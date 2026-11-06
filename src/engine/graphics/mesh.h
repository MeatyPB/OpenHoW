// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright © 2017-2022 TalonBrave.info and Others (see CONTRIBUTORS)

#pragma once

#include <list>

#include <plgraphics/plg_mesh.h>

void Mesh_GenerateFragmentedMeshNormals( const std::list< PLGMesh * > &meshes );

/**
 * Mark a fixed-size mesh's vertices (and, for triangle meshes, indices) as in use.
 *
 * PlgCreateMesh() only allocates storage: num_verts/num_indices/num_triangles stay 0
 * until PlgAddMeshVertex()/PlgAddMeshTriangle() are used. The engine fills meshes by
 * index with the PlgSetMesh*() functions instead, which never update those counts, so
 * the GL driver uploaded and drew nothing (no terrain, models or sky), and helpers
 * like PlgSetMeshUniformColour() that loop to num_verts silently did nothing.
 * Call this straight after creating the mesh, before filling it in.
 */
static inline void Mesh_SetFixedCounts( PLGMesh *mesh, unsigned int numVerts, unsigned int numTriangles = 0 ) {
	mesh->num_verts = numVerts;
	if ( numTriangles > 0 && mesh->primitive == PLG_MESH_TRIANGLES ) {
		mesh->num_triangles = numTriangles;
		mesh->num_indices = numTriangles * 3;
	}
}
