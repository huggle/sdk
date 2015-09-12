//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef HOOKS_H
#define HOOKS_H

#include "definitions.hpp"

#include <QString>

namespace Huggle
{
    class WikiUser;
    class WikiEdit;
    class Shortcut;
    class Exception;
    class MainWindow;
    class SpeedyForm;

    //! Hooks that can be used to attach some 3rd code to existing functions
    class HUGGLE_EX Hooks
    {
        public:
            static bool EditBeforeScore(WikiEdit *Edit);
            /*!
             * \brief Event that is called after edit pre process
             * \param Edit that was just pre processed
             */
            static void EditPreProcess(WikiEdit *Edit);
            static void EditBeforePostProcess(WikiEdit *Edit);
            /*!
             * \brief Event that is called after edit is post processed by internal edit processor
             * \param Edit was just post processed by huggle internal edit processor
             */
            static void EditPostProcess(WikiEdit *Edit);
            /*!
             * \brief Event that happens when edit is marked as good
             * \param Edit
             */
            static void OnGood(WikiEdit *Edit);
            /*!
             * \brief Event that happens when edit is queued for revert
             * \param Edit
             */
            static void OnRevert(WikiEdit *Edit);
            /*!
             * \brief Event that checks if edit can be considered processed
             *
             * In case there are some extensions that add extra stuff to edit processing (such as extra queries) and need to wait
             * for them to finish, they can return false here in case they are still waiting for some query to finish
             * so that this edit is hold in a queue instead of being distributed to interface. This is useful in case you make
             * extension that needs to execute asynchronous jobs during the processing of each edit.
             *
             * Until this function returns true edit is hold in a queue
             * \param Edit
             * \return
             */
            static bool EditCheckIfReady(WikiEdit *Edit);
            static bool RevertPreflight(WikiEdit *Edit);
            /*!
             * \brief Event that happens when user attempt to send a warning to editor of page
             * \param User
             */
            static void OnWarning(WikiUser *User);
            /*!
             * \brief Event that happens when edit is flagged as suspicious modification
             * \param Edit
             */
            static void Suspicious(WikiEdit *Edit);
            /*!
             * \brief When the score of user is changed
             * \param User pointer to user whom score is changed
             * \param Score New score of user
             */
            static void BadnessScore(WikiUser *User, int Score);
            static bool Speedy_BeforeOK(Huggle::WikiEdit *edit, SpeedyForm *form);
            static void Speedy_Finished(Huggle::WikiEdit *edit, QString tags, bool success);
            /*!
             * \brief Window is loaded
             * \param window
             */
            static void MainWindow_OnLoad(MainWindow *window);
            static void MainWindow_OnRender();
            static bool MainWindow_ReloadShortcut(Shortcut *shortcut);
            static void Shutdown();
    };
}

#endif // HOOKS_H
