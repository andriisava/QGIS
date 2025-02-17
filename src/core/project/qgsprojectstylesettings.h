/***************************************************************************
    qgsprojectstylesettings.h
    ---------------------------
    begin                : May 2022
    copyright            : (C) 2022 by Mathieu Pellerin
    email                : nirvn dot asia at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSPROJECTSTYLESETTINGS_H
#define QGSPROJECTSTYLESETTINGS_H

#include "qgis_core.h"
#include "qgstextformat.h"
#include "qgswkbtypes.h"

#include <memory.h>

class QDomElement;
class QgsReadWriteContext;
class QDomDocument;
class QgsProject;
class QgsSymbol;
class QgsColorRamp;

/**
 * \brief Contains settings and properties relating to how a QgsProject should handle
 * styling.
 *
 * \ingroup core
 * \since QGIS 3.26
 */
class CORE_EXPORT QgsProjectStyleSettings : public QObject
{
    Q_OBJECT

  public:

    /**
     * Constructor for QgsProjectStyleSettings for the specified \a project.
     *
     * Ownership is transferred to the \a project.
     */
    QgsProjectStyleSettings( QgsProject *project = nullptr );

    /**
     * Returns the project default symbol for a given type.
     * \param symbolType the symbol type
     * \returns a symbol pointer or NULL if there is no default set
     * \note the symbol ownership is transferred to the caller
     */
    QgsSymbol *defaultSymbol( Qgis::SymbolType symbolType ) const SIP_FACTORY;

    /**
     * Sets the project default symbol for a given type.
     * \param symbolType the symbol type
     * \param symbol the symbol pointer, set to NULL to clear default
     * \note the symbol ownership is not transferred
     */
    void setDefaultSymbol( Qgis::SymbolType symbolType, QgsSymbol *symbol );

    /**
     * Returns the project default color ramp.
     * \returns a color ramp pointer or NULL if there is no default set
     * \note the color ramp ownership is transferred to the caller
     */
    QgsColorRamp *defaultColorRamp() const SIP_FACTORY;

    /**
     * Sets the project default color ramp.
     * \param colorRamp the color ramp, set to NULL to clear default
     * \note the color ramp ownership is not transferred
     */
    void setDefaultColorRamp( QgsColorRamp *colorRamp );

    /**
     * Returns the project default text format.
     * \note if no default is defined, the returned format will be invalid
     */
    QgsTextFormat defaultTextFormat() const;

    /**
     * Sets the project default text format.
     * \param textFormat the text format, an invalid format is interpreted as no default
     */
    void setDefaultTextFormat( QgsTextFormat textFormat );

    /**
     * Returns whether the default symbol fill color is randomized.
     */
    bool randomizeDefaultSymbolColor() const { return mRandomizeDefaultSymbolColor; }

    /**
     * Sets whether the default symbol fill color is randomized.
     */
    void setRandomizeDefaultSymbolColor( bool randomized ) { mRandomizeDefaultSymbolColor = randomized; }

    /**
     * Returns the default symbol opacity.
     */
    double defaultSymbolOpacity() const { return mDefaultSymbolOpacity; }

    /**
     * Sets the default symbol opacity.
     */
    void setDefaultSymbolOpacity( double opacity ) { mDefaultSymbolOpacity = opacity; }

    /**
     * Resets the settings to a default state.
     */
    void reset();

    /**
     * Reads the settings's state from a DOM element.
     * \see writeXml()
     */
    bool readXml( const QDomElement &element, const QgsReadWriteContext &context );

    /**
     * Returns a DOM element representing the settings.
     * \see readXml()
     */
    QDomElement writeXml( QDomDocument &doc, const QgsReadWriteContext &context ) const;

  private:

    QgsProject *mProject = nullptr;

    std::unique_ptr< QgsSymbol > mDefaultMarkerSymbol;
    std::unique_ptr< QgsSymbol > mDefaultLineSymbol;
    std::unique_ptr< QgsSymbol > mDefaultFillSymbol;
    std::unique_ptr< QgsColorRamp > mDefaultColorRamp;
    QgsTextFormat mDefaultTextFormat;

    bool mRandomizeDefaultSymbolColor = true;
    double mDefaultSymbolOpacity = 1.0;

};

#endif // QGSPROJECTSTYLESETTINGS_H
