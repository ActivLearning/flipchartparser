/** @file asactionlaunchminiapp.h
 * Defines the AsActionLaunchMiniApp class.
 * Copyright (C) 2006-2011 Promethean Limited. All Rights Reserved.
 */

#ifndef ASACTIONLAUNCHMINIAPP_H
#define ASACTIONLAUNCHMINIAPP_H

#include "asaction.h"

class AsFactory;
class AsUser;

/**
 * Represents an action object in a flipchart that launches a mini-app.
 */
class AsActionLaunchMiniApp : public AsAction
{




public:
    AsActionLaunchMiniApp( AsFactory * pAsFactory);

    AsActionLaunchMiniApp( const AsActionLaunchMiniApp& );
    AsActionLaunchMiniApp& operator= ( const AsActionLaunchMiniApp& );

    /**
     * Will attempt to launch the application if found. Will display error dialogs if not found or atlas framework returns an error.
     */
    void asRun( AsUser*, QPointF );

public: //Properties.
    void asResetPropertyIndex();

    /**
     * Returns the UUID of the mini-application
     */
    const QString& asGetAppUUID() const;

    /**
     * Sets the mini-application UUID to launch.
     * @param aAppUUID The application UUID
     */
    void asSetAppUUID(const QString& aAppUUID);


   /**
     * Returns the last known name of mini-application.
     * This is the name the application when the action was created and we store it in the current locale.
     * This name is used when the mini-application doesn't exist on the target PC and there we display this name in the error message
     */
    const QString& asGetLastKnownAppName() const;

    /**
     * Sets the last known name of the mini-application
     * @param aAppName The application human readable name
     */
    void asSetLastKnownAppName(const QString& aAppName);

    QString typeName() override;

private:
    void asCopy( const AsActionLaunchMiniApp& );
    static QHash<QString, quint16>& m_lProperties();

private:
    QString m_appUUID;
    QString m_lastKnownAppName;
};

#endif // AsActionLaunchMiniApp_H
