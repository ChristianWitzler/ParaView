/*=========================================================================

   Program:   ParaQ
   Module:    pqThresholdPanel.cxx

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaQ is a free software; you can redistribute it and/or modify it
   under the terms of the ParaQ license version 1.1. 

   See License_v1.1.txt for the full ParaQ license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

// this include
#include "pqThresholdPanel.h"

// Qt includes
#include <QSlider>

// VTK includes

// paraview includes

// paraq includes
#include "pqSliderDomain.h"


/// constructor
pqThresholdPanel::pqThresholdPanel(QWidget* p)
  : pqLoadedFormObjectPanel(":/pqWidgets/CustomThreshold.ui", p)
{
}

/// destructor
pqThresholdPanel::~pqThresholdPanel()
{
  this->setProxy(NULL);
}

/// set the proxy to display properties for
void pqThresholdPanel::setProxy(pqSMProxy p)
{
  if(this->Proxy)
    {
    // detach domains
    QSlider* slider = this->findChild<QSlider*>("ThresholdBetweenSlider:0");
    if(slider)
      {
      QObject* d = slider->findChild<QObject*>("Domain");
      Q_ASSERT(d != NULL);
      delete d;
      }
    slider = this->findChild<QSlider*>("ThresholdBetweenSlider:1");
    if(slider)
      {
      QObject* d = slider->findChild<QObject*>("Domain");
      Q_ASSERT(d != NULL);
      delete d;
      }
    }
  this->pqLoadedFormObjectPanel::setProxy(p);
  if(this->Proxy)
    {
    // attach domains
    QSlider* slider = this->findChild<QSlider*>("ThresholdBetweenSlider:0");
    if(slider)
      {
      pqSliderDomain* d = new pqSliderDomain(slider, 
                          this->Proxy->GetProperty("ThresholdBetween"),
                          0);
      d->setObjectName("Domain");
      d->domainChanged();
      }
    slider = this->findChild<QSlider*>("ThresholdBetweenSlider:1");
    if(slider)
      {
      pqSliderDomain* d = new pqSliderDomain(slider, 
                          this->Proxy->GetProperty("ThresholdBetween"),
                          1);
      d->setObjectName("Domain");
      d->domainChanged();
      }
    }
}

