/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:53:59 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 19:08:10 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_CODES_H
# define EXIT_CODES_H

//command line run commands' error codes
# define ERR_MISC 1
# define ERR_NOT_EXEC 126
# define ERR_NOT_FOUND 127
# define ERR_INV_EXIT 128
# define ERR_FATAL_SIG 128
# define ERR_CTRL_C 130
# define ERR_OUT_RANGE 255

//bash exit codes
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_CMD_ERROR 2
#endif