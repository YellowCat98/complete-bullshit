#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <cue/PlayerIcon.hpp>

using namespace geode::prelude;

#define MOD_ENABLED Mod::get()->getSettingValue<bool>("cpu-core-enabled")

class $modify(CPUCoreSprite, LoadingLayer) {
	bool init(bool refresh) {
		if (!LoadingLayer::init(refresh)) return false;
		if (!MOD_ENABLED) return true;

		unsigned int cores = std::thread::hardware_concurrency();

		auto menu = CCMenu::create();
		menu->setContentWidth(this->getContentWidth());
		menu->setID("cpu-cores-sprite"_spr);
		menu->setAnchorPoint({0.0f, 1.0f});
		menu->setLayout(
			RowLayout::create()
			->setAxisAlignment(AxisAlignment::Start)
			->setGap(5.0f)
			->setAutoScale(false)
		);

		auto gm = GameManager::get();

		auto icon = cue::Icons{
			.type = IconType::Cube,
			.id = gm->getPlayerFrame(),
			.color1 = gm->getPlayerColor(),
			.color2 = gm->getPlayerColor2(),
			.glowColor = gm->getPlayerGlow() ? gm->getPlayerGlowColor() : -1
		};

		for (int i = 0; i != cores; ++i) {
			auto player = cue::PlayerIcon::create(icon);
			menu->addChild(player);
		}

		menu->updateLayout();

		this->addChildAtPosition(menu, Anchor::TopLeft, {0.0f, 0.0f}, false);

		return true;
	}
};