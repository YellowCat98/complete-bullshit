#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

#define MOD_ENABLED Mod::get()->getSettingValue<bool>("doom-enabled")

class $modify(DoomExitMessage, MenuLayer) {
	struct Fields {
		std::vector<std::string> m_messages = {
			"Are you sure you want to <cr>quit</c> this great game?",
			"Please don't leave, there's more <cr>demons</c> to toast!",
			"Let's beat it -- this is turning into a <cr>bloodbath</c>!",
			"I wouldn't leave if i were you. <cr>DOS</c> is much worse.",
			"You're trying to say you like <cr>DOS</c> better than me, right?",
			"Don't leave yet -- there's a <cr>demon</c> around that corner!",
			"Ya know, next time you come in here, I'm gonna <cr>toast</c> ya.",
			"Go ahead and <cr>leave</c>. See if i care.",
		};
	};
	void onQuit(CCObject* sender) {
		if (!MOD_ENABLED) return MenuLayer::onQuit(sender);

		int index = utils::random::generate(0, m_fields->m_messages.size());
		std::string message = m_fields->m_messages[index];

		geode::createQuickPopup(
			"Quit Game",
			message,
			"Cancel", "Yes",
			[](FLAlertLayer*, bool btn2) {
				if (btn2) utils::game::exit(true);
			}
		);
	}
};