#include "duneanaobj/StandardRecord/StandardRecord.h"

#include <ROOT/RNTupleReader.hxx>
#include "TH1D.h"
#include <TFile.h>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  auto reader = ROOT::RNTupleReader::Open("caf", argv[1]);
  auto srView = reader->GetView<caf::StandardRecord>("rec");

  TH1D *vtx_x = new TH1D("vtx_x", "Vertex X", 100, -400, 400);
  TH1D *vtx_y = new TH1D("vtx_y", "Vertex Y", 100, -300, 200);
  TH1D *vtx_z = new TH1D("vtx_z", "Vertex Z", 100, 300, 1000);

  for (auto entryId : reader->GetEntryRange()) {
    const auto sr = srView(entryId);
    for (const auto &ixn : sr.common.ixn.dlp) {
      vtx_x->Fill(ixn.vtx.x);
      vtx_y->Fill(ixn.vtx.y);
      vtx_z->Fill(ixn.vtx.z);
    }
  }

  TFile outFile("neutrino_vertices.root", "RECREATE");
  vtx_x->Write();
  vtx_y->Write();
  vtx_z->Write();
  outFile.Close();

  return 0;
}