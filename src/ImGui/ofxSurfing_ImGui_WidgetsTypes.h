#pragma once

#include "ofMain.h"

#include <list>
#include <iostream>
#include <boost/range/adaptor/reversed.hpp>

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutManager.h"
#include "ofxSurfing_ImGui_WidgetsButtons.h"

namespace ofxSurfing {

	//namespace ImTypes {
	//	enum ImWidgetSurfingTYPE
	//	{
	//		IM_DEFAULT = 0,
	//		IM_HIDDEN,
	//		//bool
	//		IM_CHECKBOX,
	//		IM_BUTTON_SMALL,
	//		IM_BUTTON_BIG,
	//		IM_TOGGLE_SMALL,
	//		IM_TOGGLE_BIG,
	//		//float/int
	//		IM_SLIDER,
	//		IM_STEPPER,
	//		IM_DRAG,
	//		//IM_TEXT_BIG,
	//		NUM_IM_TYPES
	//	};
	//}

	class SurfingWidgetTypes {

		//-

	public:
		//TODO: make simpler namespace. move outside the class?
		enum ImWidgetSurfingTYPE
		{
			IM_DEFAULT = 0,
			IM_HIDDEN,
			IM_CHECKBOX,//bool
			IM_BUTTON_SMALL,
			IM_BUTTON_BIG,
			IM_TOGGLE_SMALL,
			IM_TOGGLE_BIG,
			IM_SLIDER,//float/int
			IM_STEPPER,
			IM_DRAG,
			//IM_TEXT_BIG,
			NUM_IM_TYPES
		};

		//-

		//TODO:
		// a getUniqueName alternative
	//public:
	//	int index = 0;
	//	void resetIndex() {
	//		index = 0;
	//	}
	//	std::string getTag(ofAbstractParameter& aparam) {
	//		string tag = aparam.getName() + ofToString(index++);
	//		return tag;
	//	}

		//-

	public:
		// widgets sizes
		float _spcx;
		float _spcy;
		float _w100;
		float _h100;
		float _w99;
		float _w50;
		float _w33;
		float _w25;
		float _h;

		//-

		// refresh current panel shape to update widgets sizes
		void refreshPanelShape()
		{
			ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

			////TODO:
			////confirm that is not actuating
			//_w100 = ofRandom(500);
			//_w50 = ofRandom(500);
		}

		//-

		class surfingImWidgetConf {
		public:
			ImWidgetSurfingTYPE type = IM_DEFAULT;
			std::string name = "-1";
			int amtPerRow = 1;
			bool bSameLine = false;
			int spacing = -1;
		};

		//-

		vector<surfingImWidgetConf> widgetsConfs;

		SurfingWidgetTypes::SurfingWidgetTypes() {
			widgetsConfs.clear();
		}

		//-

		surfingImWidgetConf getWidgetConf(ofAbstractParameter& aparam) {

			// https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
			//std::list<int> x{ 2, 3, 5, 7, 11, 13, 17, 19 };
			//for (auto i : boost::adaptors::reverse(x))
			//	std::cout << i << '\n';
			//for (auto i : x)
			//	std::cout << i << '\n';
			//for (auto c : boost::adaptors::reverse(widgetsConfs)) // reverse?

			for (auto c : widgetsConfs)
			{
				if (c.name == aparam.getName()) // param was added to the queue
				{
					return c;
				}
			}

			//-

			// if return has not been called yet here,
			// then there's no conf added (AddWidgetConf) for the parameter
			// we return a kind of error type to be detected
			// and to be drawn with the default style.
			surfingImWidgetConf cError;
			cError.name = "-1";
			return cError;

			//surfingImWidgetConf confDefault;
			//confDefault.name = aparam.getName();
			//confDefault.bSameLine = false;
			//confDefault.amtPerRow = 1;
			//confDefault.spacing = -1;
			//return confDefault;
		}

		//-

		//TODO:
		// add remover element?

		// queue a customization config for future populate a param widget
		void AddWidgetConf(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type = IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		{
			surfingImWidgetConf c;
			c.name = aparam.getName();
			c.type = type;
			c.bSameLine = bSameLine;
			c.amtPerRow = amtPerRow;
			c.spacing = spacing;

			widgetsConfs.push_back(c);
		}

		// if we are not using the Types Engine, we will bypass the creation of widgets on ofxSurfing_ImGui_Helpers
		// then we will populate each widget type as the default appearance!
		bool isOperative() {
			return (widgetsConfs.size() > 0);
		}

		//-

		//bool Add(ofAbstractParameter& aparam, SurfingWidgetTypes type) {
		//	Add(bMode1, SurfingWidgetTypes::IM_TOGGLE_SMALL, 3, true);
		//}

		//-

		//void AddWidgetConf(string name, ImWidgetSurfingTYPE type) {
		//	surfingImWidgetConf e;
		//	e.name = name;
		//	e.type = type;
		//	widgetsConfs.push_back(e);
		//}

		//-

		ImWidgetSurfingTYPE getType(ofAbstractParameter& aparam)
		{
			string name = aparam.getName();
			ImWidgetSurfingTYPE rtype = ImWidgetSurfingTYPE(IM_DEFAULT);

			auto type = aparam.type();
			bool isBool = type == typeid(ofParameter<bool>).name();
			if (!isBool) return rtype;

			for (auto w : widgetsConfs)
			{
				if (w.name == name)
				{
					rtype = ImWidgetSurfingTYPE(w.type);
				}
			}

			return rtype;
		}

		//-

		// populate now a parameter ImGui widget
		// remember that must be called inside an ImGui::Begin/End() aka ImGui window/panel !
		bool Add(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type = IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		{
			bool bDone = false;

			// if setted as hidden dont draw, but apply same line and spacing
			if (type == IM_HIDDEN)
			{
				// extra options
				if (bSameLine) ImGui::SameLine();
				if (spacing != -1) {
					ImGui::Dummy(ImVec2(0.0f, (float)spacing));// spacing
				}

				return false;
			}

			//-

			////getUniqueName workaround
			//string tag = widgetsManager.getTag(aparam);
			//ImGui::PushID(tag.c_str());

			//----

			auto ptype = aparam.type();
			bool isBool = ptype == typeid(ofParameter<bool>).name();
			bool isFloat = ptype == typeid(ofParameter<float>).name();
			bool isInt = ptype == typeid(ofParameter<int>).name();

			// is not called with groups here..
			//bool isGroup = ptype == typeid(ofParameterGroup).name();
			//if (isGroup) 
			//{
			//	refreshPanelShape();
			//	return false;
			//}


			bool bReturn = false;

			float _ww;
			if (amtPerRow == 2) _ww = _w50;
			else if (amtPerRow == 3) _ww = _w33;
			else if (amtPerRow == 4) _ww = _w25;
			else _ww = _w100;

			if (isBool)
			{
				ofParameter<bool> p = aparam.cast<bool>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IM_BUTTON_SMALL:
					bReturn = ofxSurfingHelpers::AddBigButton(p, _ww, _h / 2);
					break;

				case IM_BUTTON_BIG:
					bReturn = ofxSurfingHelpers::AddBigButton(p, _ww, _h);
					break;

				case IM_TOGGLE_SMALL:
					bReturn = ofxSurfingHelpers::AddBigToggle(p, _ww, _h / 2);
					break;

				case IM_TOGGLE_BIG:
					bReturn = ofxSurfingHelpers::AddBigToggle(p, _ww, _h);
					break;

				case IM_DEFAULT:
				case IM_CHECKBOX:
					//default:
				{
					ImGui::PushID(1);
					if (ImGui::Checkbox(p.getName().c_str(), (bool *)&tmpRef))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				}
				break;
				}

				bDone = true;
			}

			//-

			else if (isFloat)
			{
				ofParameter<float> p = aparam.cast<float>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IM_DEFAULT:
				case IM_SLIDER:
				{
					ImGui::PushID(1);
					if (ImGui::SliderFloat(p.getName().c_str(), (float *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IM_DRAG:
				{
					const float speed = 0.01f;
					ImGui::PushID(1);
					if (ImGui::DragFloat(p.getName().c_str(), (float *)&tmpRef, speed, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IM_STEPPER:
				{
					const float step = 0.001f;
					const float stepFast = 0.1f;
					auto tmpRef = p.get();
					ImGui::PushID(1);
					if (ImGui::InputFloat(p.getName().c_str(), (float *)&tmpRef, step, stepFast))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;
				}

				bDone = true;
			}

			//-

			else if (isInt)
			{
				ofParameter<int> p = aparam.cast<int>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IM_DEFAULT:
				case IM_SLIDER:
				{
					ImGui::PushID(1);
					if (ImGui::SliderInt(p.getName().c_str(), (int *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IM_DRAG:
				{
					const float speed = 0.1;
					ImGui::PushID(1);
					if (ImGui::DragInt(p.getName().c_str(), (int *)&tmpRef, speed, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IM_STEPPER:
				{
					const int step = 1;
					const int stepFast = 5;
					auto tmpRef = p.get();
					ImGui::PushID(1);
					if (ImGui::InputInt(p.getName().c_str(), (int *)&tmpRef, step, stepFast))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;
				}

				bDone = true;
			}

			//-

			if (bDone)
			{
				// extra options
				if (bSameLine) ImGui::SameLine();
				if (spacing != -1) {
					ImGui::Dummy(ImVec2(0.0f, (float)spacing));// spacing
				}
			}

			//----

			////getUniqueName workaround
			//ImGui::PopID();

			return bReturn;
		}
	};
}// namespace ofxSurfing