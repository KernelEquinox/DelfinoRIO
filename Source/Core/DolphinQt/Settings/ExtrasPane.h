// Copyright 2017 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <vector>

#include <QWidget>

class QCheckBox;
class QComboBox;
class QLabel;
class QRadioButton;
class QSlider;
class QDateTimeEdit;

namespace Core
{
enum class State;
}

class ExtrasPane final : public QWidget
{
  Q_OBJECT
public:
  explicit ExtrasPane(QWidget* parent = nullptr);

private:
  void CreateLayout();
  void ConnectLayout();
  void Update();

  QCheckBox* m_coverage_enable_checkbox;
};
