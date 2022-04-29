#include "ofApp.h"

/*

TODO:

	fix names colliding
	add style tags to full integrate into layout engine

*/

//--------------------------------------------------------------
void ofApp::setup() {

	guiManager.setup();

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	guiManager.begin();
	{
		{
			ImGuiColorEditFlags _flagw;
			string name;

			_flagw = guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;

			name = "Knobs";
			guiManager.beginWindow(name.c_str(), NULL, _flagw);
			{
				guiManager.Add(guiManager.bAutoResize);

				//-

				// Legacy Non Styled Knobs ofParams

				ImGui::Text("LEGACY NON STYLED KNOBS OF PARAMS");
				ofxImGuiSurfing::AddSpacingDouble(); 
				
				guiManager.Add(valueKnob1, OFX_IM_KNOB, 4, true);
				guiManager.Add(valueKnob2, OFX_IM_KNOB, 4, true);
				guiManager.Add(valueKnob3, OFX_IM_KNOB, 4, true);
				guiManager.Add(valueKnob4, OFX_IM_KNOB, 4, false);

				ofxImGuiSurfing::AddKnob(valueKnob2);
				
				ofxImGuiSurfing::AddSpacingSeparated();

				//-

				// Styled Knobs ofParams

				ImGui::Text("STYLED KNOBS OF PARAMS");
				ofxImGuiSurfing::AddSpacingDouble();

				ImGui::Text("FLOAT OF PARAMS");
				ofxImGuiSurfing::AddSpacingDouble();

				float size1 = 60;
				ofxImGuiSurfing::AddKnobStyled(valueKnob1, OFX_IMGUI_KNOB_TICKKNOB, size1, "%.1f");
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob2, OFX_IMGUI_KNOB_DOTKNOB, size1, "%.1f dB");
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob3, OFX_IMGUI_KNOB_WIPERKNOB, size1, "%.3f");
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob4, OFX_IMGUI_KNOB_WIPERONLYKNOB, size1, "%.1f");

				ofxImGuiSurfing::AddSpacingBig();

				ImGui::Text("INT OF PARAMS");
				ofxImGuiSurfing::AddSpacingDouble();

				float size2 = 90;
				ofxImGuiSurfing::AddKnobStyled(valueKnob5, OFX_IMGUI_KNOB_TICKKNOB, size2);
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob6, OFX_IMGUI_KNOB_DOTKNOB, size2);

				ofxImGuiSurfing::AddKnobStyled(valueKnob7, OFX_IMGUI_KNOB_WIPERKNOB, size2);
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob8, OFX_IMGUI_KNOB_WIPERONLYKNOB, size2);

				//--

				ofxImGuiSurfing::AddSpacingHugeSeparated();

				// Raw ImGui Knobs

				static float value1 = 0;
				static float value2 = 0;

				ImGui::Text("IMGUI RAW KNOBS FLOAT TYPES");
				ofxImGuiSurfing::AddSpacingDouble();

				float size = 80;

				if (ImGuiKnobs::Knob("Value 1", &value1, -6.0f, 6.0f, 12 / 350.f, "%.1fdB", ImGuiKnobVariant_Tick, size, ImGuiKnobFlags_DragHorizontal))
				{
				}
				ImGui::SameLine();

				if (ImGuiKnobs::Knob("Value 2", &value2, -6.0f, 6.0f, 12 / 350.f, "%.1fdB", ImGuiKnobVariant_WiperDot, size, ImGuiKnobFlags_DragHorizontal))
				{
				}
				ImGui::SameLine();
			}
			guiManager.endWindow();
		}
	}
	guiManager.end();
}
