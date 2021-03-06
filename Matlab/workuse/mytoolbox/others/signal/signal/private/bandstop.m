function [DH,DW] = bandstop(N, F, GF, W, delay)
%BANDSTOP Desired frequency response for bandstop filters.
%  CREMEZ(N,F,'bandstop', ...) designs a linear-phase bandstop filter
%  response using CREMEZ.
%
%  CREMEZ(N,F,{'bandstop', D}, ...) specifies group-delay offset D such
%  that the filter response will have a group delay of N/2 + D in
%  units of the sample interval, where N is the filter order.
%  Negative values create less delay, while positive values create
%  more delay.  By default, D=0.
%
%  The symmetry option SYM defaults to 'even' if unspecified in the
%  call to CREMEZ, if no negative band edge frequencies are
%  specified in F.
%
%  EXAMPLE: Design a 31-tap, complex lowpass filter
%    b = cremez(30,[-1 -.5 -.4 .7 .8 1],'bandstop');
%    freqz(b,1,512,'whole');
%
%  EXAMPLE: Reduced group delay filter response:
%    b = cremez(30,[0 .6 .7 1],{'bandstop',-1});
%
%  See also CREMEZ.

%   Authors: L. Karam, J. McClellan
%   Revised: October 1996, D. Orofino
%
%   Copyright (c) 1988-98 by The MathWorks, Inc.
%   $Revision: 1.1 $  $Date: 1998/06/03 16:14:36 $

%  [DH,DW]=BANDSTOP(N,F,GF,W,DELAY)
%       N: filter order (length minus one)
%       F: vector of band edges
%      GF: vector of frequencies at which to evaluate
%       W: vector of weights, one per band
%   DELAY: negative slope of the phase.
%           M/2=(L-1)/2 for exact linear phase.
%
%      DH: vector of desired filter response (mag & phase)
%      DW: vector of weights (positive)
%
% NOTE: DH(f) and DW(f) are specified as functions of frequency

% Support query by CREMEZ for the default symmetry option:
if nargin==2,
  % Return symmetry default - pass call off to multiband:
  if length(F)>4, F(6)=F(5); end;  F(5)={[]};  % Construct dummy mags vector
  DH=multiband(N,F);
  return
end

% Standard call:
error(nargchk(4,5,nargin));
if nargin<5, delay = 0; end
% multiband will adjust for linear phase

Le   = length(F);
mags = [1;1] * rem(1:Le/2, 2); mags = mags(:);
jkl  = find( F(1:Le-1).*F(2:Le) <= 0 );
if rem(jkl(1)-1,4), mags = 1-mags; end

[DH,DW] = multiband(N, F, GF, W, mags, delay);

% end of bandstop.m
