/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Speech module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/



#include "qtexttospeech.h"
#include "qtexttospeech_p.h"

#include <qdebug.h>

QT_BEGIN_NAMESPACE


// FIXME: check that the private copying actually works
// FIXME: disentangle SPD from the generic stuff


QTextToSpeechPrivate::QTextToSpeechPrivate(QTextToSpeech *speech)
    : m_speech(speech), m_state(QTextToSpeech::Ready)
{
}

/*!
  \class QTextToSpeech
  \brief The QTextToSpeech class provides a convenient access to text-to-speech engines
  \inmodule QtSpeech

  Use \l say() to start synthesizing text.
  It is possible to specify the language with \l setLocale().
  To select between the available voices use \l setVoice().
  The languages and voices depend on the available synthesizers on each platform.
  On Linux by default speech-dispatcher is used.
*/

/*!
  \fn explicit QTextToSpeech::QTextToSpeech(QObject *parent=0)

  Constructs a QTextToSpeech object as the child of \a parent.
*/

/*!
  \enum QTextToSpeech::State
  \value Ready          The synthesizer is ready to start a new text. This is
                        also the state after a text was finished.
  \value Speaking       The current text is being spoken.
  \value Paused         The sythetization was paused and can be resumed with \l resume().
  \value BackendError   The backend was unable to synthesize the current string.
*/

/*!
  \property QTextToSpeech::state
  This property holds the current state of the speech synthesizer.
  Use \l say() to start synthesizing text with the current voice and locale.

*/

QTextToSpeech::State QTextToSpeech::state() const
{
    Q_D(const QTextToSpeech);
    return d->state();
}

/*!
  Start synthesizing the \a text.
  This function will start the asynchronous speaking of the text.
  The current state is available using the \l state property. Once the
  synthetization is done, a \l stateChanged() signal with the \l Ready state
  will be emitted.
*/
void QTextToSpeech::say(const QString &text)
{
    Q_D(QTextToSpeech);
    d->say(text);
}

/*!
  Stop the currently speaking text.
*/
void QTextToSpeech::stop()
{
    Q_D(QTextToSpeech);
    d->stop();
}

/*!
  Pause the current speech.
  \note this function depends on the platform and backend and may not work at all,
  take several seconds until it takes effect or may pause instantly.
  Some synthesizers will look for a break that they can later resume from, such as
  a sentence end.
  \note Due to Android platform limitations, pause() stops the current utterance,
  while resume() starts the previously queued utterance from the beginning.
  \sa resume()
*/
void QTextToSpeech::pause()
{
    Q_D(QTextToSpeech);
    d->pause();
}

/*!
  Resume speaking after \l pause() has been called.
  \sa pause()
*/
void QTextToSpeech::resume()
{
    Q_D(QTextToSpeech);
    d->resume();
}

//QVector<QString> QTextToSpeech::availableVoiceTypes() const
//{
//    Q_D(const QTextToSpeech);
//    return d->availableVoiceTypes();
//}

//void QTextToSpeech::setVoiceType(const QString& type)
//{
//    Q_D(QTextToSpeech);
//    d->setVoiceType(type);
//}
//QString QTextToSpeech::currentVoiceType() const
//{
//    Q_D(const QTextToSpeech);
//    return d->currentVoiceType();
//}


/*!
 \property QTextToSpeech::pitch
 This property holds the voice pitch in the range -1.0 to 1.0.
 The default of 0.0 is normal speech pitch.
*/

void QTextToSpeech::setPitch(double pitch)
{
    Q_D(QTextToSpeech);
    d->setPitch(pitch);
}

double QTextToSpeech::pitch() const
{
    Q_D(const QTextToSpeech);
    return d->pitch();
}

/*!
 \property QTextToSpeech::rate
 This property holds the current voice rate in the range -1.0 to 1.0.
 The default value of 0.0 is normal speech flow.
*/
void QTextToSpeech::setRate(double rate)
{
    Q_D(QTextToSpeech);
    d->setRate(rate);
}

double QTextToSpeech::rate() const
{
    Q_D(const QTextToSpeech);
    return d->rate();
}

/*!
 \property QTextToSpeech::volume
 This property holds the current volume in the range 0 to 100.
 The default value depends on the platform's default volume.
*/

void QTextToSpeech::setVolume(int volume)
{
    Q_D(QTextToSpeech);
    volume = qMin(qMax(volume, 0), 100);
    d->setVolume(volume);
}

int QTextToSpeech::volume() const
{
    Q_D(const QTextToSpeech);
    return d->volume();
}

/*!
 Sets the \a locale to a given locale if possible.
 The default is the system locale.
*/
void QTextToSpeech::setLocale(const QLocale &locale)
{
    Q_D(QTextToSpeech);
    d->setLocale(locale);
}

/*!
 \property QTextToSpeech::locale
 This property holds the current locale in use. By default, the system locale
 is used.
*/
QLocale QTextToSpeech::locale() const
{
    Q_D(const QTextToSpeech);
    return d->locale();
}

/*!
 Gets a vector of locales that are currently supported. Note on some platforms
 these can change when the backend changes synthesizers for example.
*/
QVector<QLocale> QTextToSpeech::availableLocales() const
{
    Q_D(const QTextToSpeech);
    return d->availableLocales();
}

/*!
 Sets the \a voice to use.

 \note On some platforms setting the voice changes other voice attributes
 such as locale, pitch, etc. in which case signals are emitted for these
 changes.
*/
void QTextToSpeech::setVoice(const QVoice &voice)
{
    Q_D(QTextToSpeech);
    d->setVoice(voice);
}

/*!
 \property QTextToSpeech::voice
 This property holds the current voice used for the speech.
*/
QVoice QTextToSpeech::voice() const
{
    Q_D(const QTextToSpeech);
    return d->voice();
}

/*!
 Gets a vector of voices available for the current locale.
 \note if no locale has been set, the system locale is used.
*/
QVector<QVoice> QTextToSpeech::availableVoices() const
{
    Q_D(const QTextToSpeech);
    return d->availableVoices();
}

QT_END_NAMESPACE
