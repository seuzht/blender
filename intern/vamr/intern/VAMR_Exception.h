/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/** \file
 * \ingroup VAMR
 */

#ifndef __VAMR_EXCEPTION_H__
#define __VAMR_EXCEPTION_H__

#include <exception>

class VAMR_Exception : public std::exception {
  friend class VAMR_Context;

 public:
  VAMR_Exception(const char *msg, const char *file, int line, int res = 0)
      : std::exception(), m_msg(msg), m_file(file), m_line(line), m_res(res)
  {
  }

  const char *what() const noexcept override
  {
    return m_msg;
  }

 private:
  const char *m_msg;
  const char *m_file;
  const int m_line;
  int m_res;
};

#endif  // __VAMR_EXCEPTION_H__
