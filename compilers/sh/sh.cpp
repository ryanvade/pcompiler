#include "sh.hpp"
#include "pcompiler/compilers.hpp"
#include "../common/platform.hpp"
#include "pcompiler/compiler_options.hpp"

#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QDebug>

using namespace Compiler;

Shell::Shell()
  : Passthrough("sh", QStringList() << "sh" << "bash")
{}

OutputList Shell::transform(const QStringList &input, Options &options) const
{
  
  Output ret;
  ret.setFiles(input);
  ret.setExitCode(0);
  QStringList mod = input;
  if(input.size() == 1) {

    QFileInfo info(mod[0]);
    const QString newName = info.absolutePath() + "/" + info.baseName();
    QFile::rename(mod[0], newName);
    mod[0] = newName;
  }
  ret.setGeneratedFiles(mod);
  ret.setTerminal(Output::BinaryTerminal);
  return OutputList() << ret;
}

REGISTER_COMPILER(Shell)