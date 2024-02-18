/*
 * This file is part of Ginkgo CADx
 *
 * Copyright (c) 2015-2016 Gert Wollny
 * Copyright (c) 2008-2014 MetaEmotion S.L. All rights reserved.
 *
 * Ginkgo CADx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with Ginkgo CADx; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <api/globals.h>
#include "wseleccion.h"
#include <main/managers/widgetsmanager.h>
#include <api/icontexto.h>
#include <api/math/geometry3d.h>
#include <vtk_glew.h>
#include <cmath>

//region "Implementacion de WSeleccionBuilder"

GNC::GCS::Widgets::WSeleccionBuilder::WSeleccionBuilder(TWidgetsManager* pManager, const GNC::GCS::TriggerButton& buttonMask, long gid) : GNC::GCS::Widgets::IWidgetBuilder(pManager, buttonMask, gid)
{
        m_MouseDown = false;
        m_Estado = WBS_Ninguno;
        m_Dentro = true;
}

GNC::GCS::Widgets::WSeleccionBuilder::~WSeleccionBuilder()
{
}

void GNC::GCS::Widgets::WSeleccionBuilder::OnMouseEvents(GNC::GCS::Events::EventoRaton& evento)
{
        if (!m_pManager) {
                return;
        }
        /*
        if (evento.Entering()) {
        	m_Dentro = true;
        	m_pManager->Modificado();
        }
        else if (evento.Leaving()) {
        	m_Dentro = false;
        	m_pManager->Modificado();
        }
        */
        if (m_MouseDown && evento.ButtonUp(m_ButtonMask)) {
                m_MouseDown = false;
                if (m_Estado != WBS_Creando) {
                        m_Estado = WBS_Ninguno;
                        return;
                }
                m_Estado = WBS_Ninguno;

                m_Stop = evento.iP;

                if (m_Start.DistanciaEuclidea(m_Stop) < GNC::GCS::Vector::EpsilonDeReales() ) {
                        evento.Skip(true);
                } else {
                        GNC::GCS::Vector a = m_Start.ProyeccionOrtogonalSobreRecta(m_Stop,  m_Stop - evento.c->ScreenDirectionCosines[0]);
                        GNC::GCS::Vector b = m_Start.ProyeccionOrtogonalSobreRecta(m_Stop,  m_Stop - evento.c->ScreenDirectionCosines[1]);
                        m_BB[0] = m_Start;
                        m_BB[1] = a;
                        m_BB[2] = m_Stop;
                        m_BB[3] = b;
                        m_pManager->PropagarHitTestSeleccion(m_BB, 4);

                        evento.Skip(false);
                }
                m_pManager->Modificado();
                m_Estado = WBS_Ninguno;
        } else if (evento.ButtonDown(m_ButtonMask)) {
                if (m_Estado != WBS_Ninguno) {
                        return;
                }
                m_MouseDown = true;

                m_Start = evento.iP;
                m_Stop = m_Start;


                m_pManager->Modificado();
                m_Estado = WBS_Creando;
                evento.Skip(false);
        } else if (evento.Dragging() && m_MouseDown) {
                if (m_Estado != WBS_Creando) {
                        return;
                }

                m_Stop = evento.iP;

                m_pManager->Modificado();
                evento.Skip(false);
        } else if( evento.Moving() ) {
                GTRACE("Moviendose");
                m_NodoMoviendose = evento.iP;
                m_Estado = WBS_Ninguno;
        }


}

void GNC::GCS::Widgets::WSeleccionBuilder::OnKeyEvents(TEventoTeclado&)
{

}

void GNC::GCS::Widgets::WSeleccionBuilder::Render(GNC::GCS::Contexto3D* c)
{

        if (m_Estado == WBS_Creando) {
                glLineWidth(1.0f);
                glColor4f(0.0f, 0.36f, 0.807f, 0.15f);
                GNC::GCS::Vector a = m_Start.ProyeccionOrtogonalSobreRecta(m_Stop,  m_Stop - c->ScreenDirectionCosines[0]);
                GNC::GCS::Vector b = m_Start.ProyeccionOrtogonalSobreRecta(m_Stop,  m_Stop - c->ScreenDirectionCosines[1]);

                glBegin(GL_QUADS);
                glVertex2dv(m_Start.v);
                glVertex2dv(a.v);
                glVertex2dv(m_Stop.v);
                glVertex2dv(b.v);
                glEnd();
                glColor4f(0.0f, 0.36f, 0.807f, 1.0f);
                glBegin(GL_LINE_LOOP);
                glVertex2dv(m_Start.v);
                glVertex2dv(a.v);
                glVertex2dv(m_Stop.v);
                glVertex2dv(b.v);
                glEnd();
        } else {

        }
}

GNC::GCS::Widgets::TipoCursor GNC::GCS::Widgets::WSeleccionBuilder::GetCursor()
{
        return GNC::GCS::Widgets::CUR_FLECHA;
}

//endregion
