// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "DolphinQt/Settings/ExtrasPane.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSignalBlocker>
#include <QSlider>
#include <QVBoxLayout>
#include <cmath>

#include "Core/Config/MainSettings.h"
#include "Core/ConfigManager.h"
#include "Core/Core.h"
#include "Core/HW/SystemTimers.h"
#include "Core/PowerPC/PowerPC.h"

#include "DolphinQt/Settings.h"

ExtrasPane::ExtrasPane(QWidget* parent) : QWidget(parent)
{
  CreateLayout();
  Update();

  ConnectLayout();

  connect(&Settings::Instance(), &Settings::EmulationStateChanged, this, &ExtrasPane::Update);
}

void ExtrasPane::CreateLayout()
{
  auto* main_layout = new QVBoxLayout();
  setLayout(main_layout);



  auto* coverage_options = new QGroupBox(tr("Coverage Options"));
  auto* coverage_options_layout = new QVBoxLayout();
  coverage_options->setLayout(coverage_options_layout);
  main_layout->addWidget(coverage_options);

  m_coverage_enable_checkbox = new QCheckBox(tr("Enable Code Coverage Collection"));
  coverage_options_layout->addWidget(m_coverage_enable_checkbox);

  auto* coverage_enable_description =
      new QLabel(tr("This option will make Dolphin collect code coverage data while in JIT mode.\n\n"

                    "This WILL make games run slower; leave this disabled if you don't know what this does."));
  coverage_enable_description->setWordWrap(true);
  coverage_options->layout()->addWidget(coverage_enable_description);



  main_layout->addStretch(1);
}

void ExtrasPane::ConnectLayout()
{
  m_coverage_enable_checkbox->setChecked(SConfig::GetInstance().bEnableCodeCoverage);
  connect(m_coverage_enable_checkbox, &QCheckBox::toggled, [this](bool enable_code_coverage) {
    SConfig::GetInstance().bEnableCodeCoverage = enable_code_coverage;
    Update();
  });
}

void ExtrasPane::Update()
{
  const bool running = Core::GetState() != Core::State::Uninitialized;
  const bool enable_code_coverage = !running;

  m_coverage_enable_checkbox->setEnabled(enable_code_coverage);
}
