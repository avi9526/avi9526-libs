
//    Copyright (C) 2022
//    Andrew V. Dromaretsky <dromaretsky@gmail.com> aka avi9526

//    This program is free software: you can redistribute it and/or modify it
//    under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or (at your
//    option) any later version.

//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
//    or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
//    License for more details.

//    You should have received a copy of the GNU Lesser General Public License
//    along with this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef BOOLFLOAT_H
#define BOOLFLOAT_H

class BoolFloatNormalized
{
public:
  BoolFloatNormalized();
  BoolFloatNormalized(const float);
  BoolFloatNormalized(const bool);
  BoolFloatNormalized(const BoolFloatNormalized&);
  ~BoolFloatNormalized();

  friend BoolFloatNormalized operator&&(BoolFloatNormalized V1,
                                        BoolFloatNormalized V2);
  friend BoolFloatNormalized operator&&(BoolFloatNormalized V1, bool V2);
  friend BoolFloatNormalized operator&&(bool V1, BoolFloatNormalized V2);
  friend BoolFloatNormalized operator||(BoolFloatNormalized V1,
                                        BoolFloatNormalized V2);
  friend BoolFloatNormalized operator^(BoolFloatNormalized V1,
                                       BoolFloatNormalized V2);
  friend BoolFloatNormalized operator!(BoolFloatNormalized V);
  BoolFloatNormalized& operator=(BoolFloatNormalized V);
  BoolFloatNormalized& operator=(bool V);
  BoolFloatNormalized& operator=(float V);

  operator bool();
  operator float();

  float Value() const;
  void Value(const float);
  void Value(const bool);
  void False();
  void True();
  bool Valid();

  float Threshold();
  void Threshold(const float Threshold);

protected:
  float Normalize(float Value);

private:
  float _Value;
  float _Threshold;
};

#endif // BOOLFLOAT_H
